#include "notepad.h"

NotePad::NotePad()
{
    this->text = new QTextEdit();
    this->th = new TextHighLighter(text->document());
    this->th->rehighlight();
    this->reader = new QXmlStreamReader();

    this->text->installEventFilter(this);

    this->tabNumber = 0;

    this->text->setWordWrapMode(QTextOption::NoWrap);
}

void NotePad::keyPressEvent(QKeyEvent *e)
{
    if ((e->key () == Qt::Key_Enter)) {
    }
}

bool NotePad::eventFilter(QObject *o, QEvent *e)
{
    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(e);


    if (e->type() == QEvent::KeyPress)
    {
        if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
        {
            return insertCharacterForKeyFiltering("\n");
        }
        else if (keyEvent->key() == Qt::Key_Greater)
        {
            addCloseMarkup();
            return true;
        }
        else if (keyEvent->key() == Qt::Key_Tab)
        {
            indent();
            return true;
        }
        else if (keyEvent->key() == Qt::Key_Control)
        {
           // currentNode();
        }
    }
    return false;
}

void NotePad::indent()
{
    int selectionStart = text->textCursor().selectionStart();
    int selectionEnd = text->textCursor().selectionEnd();

    tabNumber = 0;

    QTextCursor c = text->textCursor();

    c.setPosition(selectionStart);
    int upperBound = c.blockNumber();
    c.movePosition(QTextCursor::StartOfBlock);
    selectionStart = c.selectionStart();

    c.setPosition(selectionEnd);
    int lowerBound = c.blockNumber();
    c.movePosition(QTextCursor::StartOfBlock);
    selectionEnd = c.selectionEnd();

    QString s = text->toPlainText();
    QStringList line = s.split("\n");

    QXmlStreamReader xml(this->text->toPlainText());

    int last = 0;

    while(!xml.atEnd())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        for (int var = last; var < xml.lineNumber(); ++var) {
            indentLineWithBounds(&line, var, upperBound, lowerBound);
        }

        if(token == QXmlStreamReader::StartElement)
        {
            if(last != xml.lineNumber()) {
                last = xml.lineNumber();
                indentLineWithBounds(&line, last - 1, upperBound, lowerBound);
            }
            tabNumber++;
        }
        else if(token == QXmlStreamReader::EndElement)
        {
            tabNumber--;
            last = xml.lineNumber();
            indentLineWithBounds(&line, last - 1, upperBound, lowerBound);
        }
    }

    if(selectionStart < s.length() - 1)
    {
        text->setPlainText(line.join("\n"));
    }
    c.setPosition(selectionEnd);
    c.movePosition(QTextCursor::EndOfLine);
    text->setTextCursor(c);
   // this->updateDom(); // Provisoire
}

void NotePad::setText(QString s)
{
    text->setText(s);
}

QTextEdit *NotePad::getTextEdit() const
{
    return this->text;
}

void NotePad::onNodeNameUpdate(QDomNode n, QString newName)
{
    QString oldName = n.nodeName();

    updateNodeName(nodeWithPositionFromNode(n), oldName, newName);
    this->th->rehighlight();
}

void NotePad::onNodeDelete(QDomNode n)
{
    n = nodeWithPositionFromNode(n);

    QTextCursor c = text->textCursor();
    int begin;
    int end;

    auto goToNodeStart = [] (int *begin, QDomNode node, QString s, QTextCursor *c)->void
    {
        c->setPosition(0);
        c->movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, node.lineNumber()-1);
        c->setPosition(c->position() + node.columnNumber());
        *begin = c->position();
        QString open = "<";
        (*begin) -= 2;

        while(open.compare(s.at(*begin)) != 0)
        {
            (*begin)--;
        }
    };

    auto goToNodeEnd = [] (int begin, int *end, QString s, QString toFind)->void
    {
        QString open = "<";
        open.append(toFind).append(">");
        QString close = "</";
        close.append(toFind).append(">");

        int dyck = 1;
        begin += toFind.length();

        while(dyck != 0)
        {
            if(!open.compare(s.mid(begin, open.length())))
            {
                dyck++;
            }
            else if (!close.compare(s.mid(begin, close.length())))
            {
                dyck--;
            }
            begin++;
        }
        *end = begin + close.length() - 1;
    };

    auto deleteNode = [] (int begin, int end, QTextCursor *c)->void
    {
        c->setPosition(begin, QTextCursor::MoveAnchor);
        c->setPosition(end, QTextCursor::KeepAnchor);
        c->removeSelectedText();
    };

    auto removeLineIfEmpty = [] (QDomNode node, QTextCursor *c)->void
    {
        c->setPosition(0);
        c->movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, node.lineNumber()-1);
        c->movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);

        QRegExp q("\\S+");
        if(q.indexIn(c->selectedText()) == -1) {
            c->setPosition(c->position() + 1, QTextCursor::KeepAnchor);
            c->removeSelectedText();
        }
        else {
            c->movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, node.lineNumber()-1);
        }
    };

    goToNodeStart(&begin, n, text->toPlainText(), &c);
    goToNodeEnd(begin, &end, text->toPlainText(), n.nodeName());
    deleteNode(begin, end, &c);
    removeLineIfEmpty(n, &c);
    text->setTextCursor(c);
}

void NotePad::onRefreshRequest()
{
    //emit un signal si le xml est valide
    QXmlStreamReader xml(text->toPlainText());
    bool error = false;

    while(!xml.atEnd() & !error) {
        xml.readNext();
        if(xml.hasError())
        {
            error = true;
        }
    }

    if(!error)
    {
        updateDom();
    }

}

void NotePad::updateNodeName(QDomNode node, QString oldName, QString newName)
{
    int begin;
    int end;
    QTextCursor c = text->textCursor();

    auto goToNode = [] (int *begin, int *end, QDomNode node, QTextCursor *c)->void
    {
        c->setPosition(0);
        c->movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, node.lineNumber()-1);
        c->setPosition(c->position() + node.columnNumber());
        *begin = c->position();
        *end = c->position();
    };

    auto replaceNodeName = [] (int *begin, int *end, QString oldName, QString newName, QString text, QTextCursor *c)->void
    {
        if(*end > text.length())
        {
            *end = text.length();
        }
        QString t = text.mid(*begin, *end - *begin);
        t.replace(oldName, newName);

        c->setPosition(*begin, QTextCursor::MoveAnchor);
        c->setPosition(*end, QTextCursor::KeepAnchor);

        c->removeSelectedText();
        c->insertText(t);
    };

    auto gotoNodeStart = [] (int* begin, QString s)->void
    {
        QString open = "<";
        (*begin)--;

        do
        {
            (*begin)--;
        }
        while(open.compare(s.at(*begin)) != 0);
    };

    auto goToNodeEnd = [] (int *begin, int *end, QString s, QString toFind)->void
    {
        QString open = "<";
        open.append(toFind).append(">");
        QString close = "</";
        close.append(toFind).append(">");

        int dyck = 1;
        int pos = *begin;

        while(dyck != 0)
        {
            if(!open.compare(s.mid(pos, open.length())))
            {
                dyck++;
            }
            else if (!close.compare(s.mid(pos, close.length())))
            {
                dyck--;
            }
            pos++;
        }
        *begin = pos;
        *end = pos + close.length();
    };

    goToNode(&begin, &end, node, &c);
    goToNodeEnd(&begin, &end, text->toPlainText(), oldName);
    replaceNodeName(&begin, &end, oldName, newName, text->toPlainText(), &c);

    goToNode(&begin, &end, node, &c);
    gotoNodeStart(&begin, text->toPlainText());
    replaceNodeName(&begin, &end, oldName, newName, text->toPlainText(), &c);

    text->setTextCursor(c);
}

QDomNode NotePad::nodeWithPositionFromNode(QDomNode n) const
{
    stack<int> s = ModeleXml::pathFromRoot(n);

    QDomDocument dom;
    dom.setContent(text->toPlainText());
    int child;

    n = dom;

    while(!s.empty())
    {
        child = s.top();
        n = n.childNodes().at(child);
        s.pop();
    }
    return n;
}

QString NotePad::getStringFromDom() const
{
    this->text->setText(XmlFileManager::getFileManager()->getModele()->domToString());
}

void NotePad::updateDom()
{
    XmlFileManager::getFileManager()->getModele()->update(this->text->toPlainText());
    emit update();
}

void NotePad::indentLineWithBounds(QStringList *list, int line, int upperBound, int lowerBound)
{
    if(line >= upperBound && line <= lowerBound)
    {
        QRegExp regex("^(\\s)*");
        QString content = list->at(line).split(regex)[1];

        QString res;
        res.append(tabsString(tabNumber)).append(content);

        list->removeAt(line);
        list->insert(line, res);
    }
}

bool NotePad::insertCharacterForKeyFiltering(const QString str)
{
    QTextCursor c = text->textCursor();

    int pos = c.position();
    c.insertText(str);
    int oldPos = c.position();
    c.setPosition(pos);
    c.movePosition(QTextCursor::StartOfLine);
    pos = c.position();

    QString s = text->toPlainText();
    QString space = " ";
    int nbSpace = 0;

    while(!s.mid(pos, 1).compare(space))
    {
        nbSpace++;
        pos++;
    }

    c.setPosition(oldPos);
    c.insertText(tabsString(nbSpace/NB_SPACE));
    text->setTextCursor(c);

    return true;
}

void NotePad::addCloseMarkup()
{
    QTextCursor c = text->textCursor();
    int pos = c.position() - 1;

    QString open = "<";
    QString error1 = "\n";
    QString error2 = "/";
    QString error3 = ">";

    QString s = text->toPlainText();
    QChar at;

    while(true)
    {
        at = s.at(pos);
        if(!open.compare(at))
        {
            QString markup = s.mid(pos + 1, c.position() - pos - 1);
            markup = markup.split(" ").at(0);
            if(markup.length() > 0)
            {
                QString toAdd = "></";
                toAdd.append(markup).append(">");
                c.insertText(toAdd);
                c.setPosition(c.position() -  markup.length() - 3);
                text->setTextCursor(c);
            }
            return;
        }
        else if (!error1.compare(at) || !error2.compare(at) || !error3.compare(at))
        {
            cout << s.mid(pos + 1, c.position()).toStdString() << endl;
            c.insertText(">");
            text->setTextCursor(c);
            return;
        }
        pos--;
    }
}

QDomNode NotePad::currentNode() const
{
    QTextCursor c = this->text->textCursor();
    int line = c.blockNumber() + 1;
    int column = c.positionInBlock();
    vector<int> path;
    path.push_back(0);
    QXmlStreamReader xml(this->text->toPlainText());
    QXmlStreamReader::TokenType lastToken;
    lastToken = QXmlStreamReader::NoToken;

    xml.readNext();
    while(!xml.atEnd()) {

        if(xml.isStartElement()) {
            if(lastToken == QXmlStreamReader::StartElement) {
                path.push_back(0);
            } else {
                path[path.size() - 1]++;
            }
        }

        else if(xml.isComment()) {
            path[path.size() - 1]++;
        }

        else if(xml.isEndElement()) {
            if(lastToken == QXmlStreamReader::EndElement) {
                path.pop_back();
            }
        }

        if(xml.lineNumber() >= line && xml.columnNumber() >= column) {
            return XmlFileManager::getFileManager()->getModele()->nodeFromPath(path);
        }

        if(xml.tokenType() == QXmlStreamReader::StartElement ||
                xml.tokenType() == QXmlStreamReader::StartDocument ||
                xml.tokenType() == QXmlStreamReader::EndDocument ||
                xml.tokenType() == QXmlStreamReader::EndElement) {
            lastToken = xml.tokenType();
        }

        xml.readNext();
    }
}


QString NotePad::tabsString(int n) const
{
    QString l;
    for (int i = 0; i < n; i++) {
        for (int var = 0; var < NB_SPACE; ++var) {
            l.append(" ");
        }
    }
    return l;
}
