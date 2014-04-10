#include "notepad.h"

NotePad::NotePad()
{
    this->text = new QTextEdit();
    this->th = new TextHighLighter(text->document());
    this->reader = new QXmlStreamReader();

    this->text->installEventFilter(this);

    this->tabNumber = 0;

    this->text->setWordWrapMode(QTextOption::NoWrap);
}

void NotePad::keyPressEvent(QKeyEvent *e)
{
    if ((e->key () == Qt::Key_Enter))
    {
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
        else if (keyEvent->key() == Qt::Key_Shift)
        {
            //currentNode();
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
    this->updateDom();
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
    stack<int> s = ModeleXml::pathFromRoot(n);
    QString oldName = n.nodeName();

    QDomDocument dom;
    dom.setContent(text->toPlainText());
    n = dom;
    int child;

    while(!s.empty())
    {
        child = s.top();
        n = n.childNodes().at(child);
        s.pop();
    }

    changeTextFromNode(n, oldName, newName, child);
}

void NotePad::changeTextFromNode(QDomNode node, QString oldName, QString newName, int childNumber)
{
    int begin;
    int end;
    QTextCursor c = text->textCursor();

    auto f = [] (int *begin, int *end, QDomNode node, QTextCursor *c)->void {
        c->setPosition(0);
        c->movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, node.lineNumber()-1);
        c->setPosition(c->position() + node.columnNumber());
        *begin = c->position();
        *end = c->position();
    };

    auto f1 = [] (int *begin, int *end, QString oldName, QString newName, QString text, QTextCursor *c)->void {
        QString t = text.mid(*begin, *end - *begin);
        t.replace(oldName, newName);

        c->setPosition(*begin, QTextCursor::MoveAnchor);
        c->setPosition(*end, QTextCursor::KeepAnchor);

        c->removeSelectedText();
        c->insertText(t);
    };

    f(&begin, &end, node, &c);
    gotoNodeStart(&begin);
    f1(&begin, &end, oldName, newName, text->toPlainText(), &c);

    QDomNode temp = node.parentNode().childNodes().at(childNumber + 1);

    if(temp.isNull())
    {
        temp = node.parentNode().nextSibling();
        if(temp.isNull())
        {
            QString s = text->toPlainText();
            begin = s.length();
            QString close = "</";
            close.append(oldName).append(">");
            while(close.compare(s.mid(begin, close.length())))
            {
                begin--;
            }
            end = begin + close.length();
            f1(&begin, &end, oldName, newName, text->toPlainText(), &c);
        }
        else
        {
            f(&begin, &end, temp, &c);
            gotoNodeEnd(&begin, &end);
            f1(&begin, &end, oldName, newName, text->toPlainText(), &c);
            begin--;
            end = begin;
            gotoNodeStart(&begin);
            f1(&begin, &end, oldName, newName, text->toPlainText(), &c);
        }
    }
    else
    {
        node = temp;
        f(&begin, &end, node, &c);
        gotoNodeEnd(&begin, &end);
        f1(&begin, &end, oldName, newName, text->toPlainText(), &c);
    }



    text->setTextCursor(c);
}

void NotePad::gotoNodeStart(int* begin)
{
    QString t = text->toPlainText();

    QString open = "<";

    while(open.compare(t.at(*begin)))
    {
        (*begin)--;
    }
}

void NotePad::gotoNodeEnd(int *begin, int *end)
{
    QString t = text->toPlainText();
    QString open = "<";

    while(open.compare(t.at(*begin)))
    {
        (*begin)--;
    }
    (*begin)--;
    *end = *begin - 1;
    while(open.compare(t.at(*begin)))
    {
        (*begin)--;
    }
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

QString NotePad::currentNode() const
{
    QTextCursor c = this->text->textCursor();

    stack<QString> s;

    s.push("");

    int line = c.blockNumber() + 1;
    int column = c.positionInBlock();
    int last = 0;

    QXmlStreamReader xml(this->text->toPlainText());

    while(!xml.atEnd()) {
        if(xml.isStartElement()) {
            s.push(xml.name().toString());
        }

        if(last <= line && xml.lineNumber() >= line && xml.columnNumber() >= column) {
            cout << "node : " << s.top().toStdString() << endl;
            cout << "type : " << xml.tokenString().toStdString() << endl;
            return s.top();
        }
        if(xml.isEndElement())
        {
            s.pop();
        }
        last = xml.lineNumber();
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
