#include "notepad.h"
#include "xmlfilemanager.h"

NotePad::NotePad()
{
    this->text = new QTextEdit();
    this->linesDisplay = new QTextEdit();
    //this->logger = new QTextEdit();

    this->grid = new QGridLayout();
    this->grid->setMargin(0);
    this->grid->setSpacing(1);

    linesDisplay->setReadOnly(true);
    linesDisplay->setWordWrapMode(QTextOption::NoWrap);
    linesDisplay->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    linesDisplay->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    linesDisplay->setTextColor(Qt::darkGray);
    linesDisplay->setText("1");
    linesDisplay->setStyleSheet("* { background-color: rgb(200, 200, 200); border-color: gray; border-style: outset; border-width: 2px;}");
    linesDisplay->setFixedWidth(38);

    text->setStyleSheet("* { border-color: gray; border-style: outset; border-width: 2px;}");
    text->setWordWrapMode(QTextOption::NoWrap);

    grid->addWidget(linesDisplay, 0, 0);
    grid->addWidget(text, 0, 1);

    this->view = new QWidget();
    this->view->setLayout(grid);

    this->th = new TextHighLighter(text->document());
    this->th->rehighlight();
    this->reader = new QXmlStreamReader();

    this->text->installEventFilter(this);

    this->tabNumber = 0;

    connect(linesDisplay->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(onScroll(int)));
    connect(text->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(onScroll(int)));
    connect(text, SIGNAL(textChanged()), this, SLOT(addLinesNumber()));

    hasError = false;
}

void NotePad::keyPressEvent(QKeyEvent *e){}

QWidget* NotePad::getView() const
{
    return this->view;
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
}

void NotePad::setText(QString s)
{
    text->setText(s);
}

QString NotePad::getText() const
{
    return text->toPlainText();
}

void NotePad::onNodeNameUpdate(QDomNode n, QString newName)
{
    QString oldName = n.nodeName();

    updateNodeName(n, oldName, newName);
    this->th->rehighlight();
}

void NotePad::onNodeDelete(QDomNode n)
{
    auto vequal = [](vector<int> v1, vector<int> v2)->bool
    {
            if(v1.size() == v2.size())
            {
                    for (int i = 0; i < v1.size(); ++i) {
                if(v2[i] != v1[i])
                {
                    return false;
                }
            }
            return true;
        }
        return false;
    };

    auto goToNodeStart = [] (int *begin, QString s)->void
    {
        QString open = "<";
        while(open.compare(s.at(*begin)) != 0)
        {
            (*begin)--;
        }
    };

    stack<int> st = ModeleXml::pathFromRoot(n);
    vector<int> nodePath;

    while(!st.empty())
    {
        nodePath.push_back(st.top());
        cout << "" << st.top() << endl;
        st.pop();
    }

    nodePath[0]++;
    vector<int> path;
    path.push_back(0);
    QXmlStreamReader xml(text->toPlainText());
    QXmlStreamReader::TokenType lastToken;
    lastToken = QXmlStreamReader::NoToken;
    QTextCursor c = text->textCursor();

    int begin;
    int end;
    int nbFound = 0;

    xml.readNext();
    while(!xml.atEnd()) {
        if(xml.isStartElement()) {
            if(lastToken == QXmlStreamReader::StartElement) {
                path.push_back(0);
            } else {
                path[path.size() - 1]++;
            }
        }

        else if(xml.isEndElement()) {
            if(lastToken == QXmlStreamReader::EndElement) {
                path.pop_back();
            }
        }

        if(vequal(path, nodePath))
        {
            if(nbFound == 0)
            {
                nbFound++;
                c.setPosition(0);
                c.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, xml.lineNumber()-1);
                c.setPosition(c.position() + xml.columnNumber(), QTextCursor::KeepAnchor);
                begin = c.position();
                goToNodeStart(&begin, text->toPlainText());
            }
            else if (nbFound == 1 && xml.name().size() > 0)
            {
                c.setPosition(0);
                c.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, xml.lineNumber()-1);
                c.setPosition(c.position() + xml.columnNumber(), QTextCursor::KeepAnchor);
                end = c.position();
                c.setPosition(begin, QTextCursor::MoveAnchor);
                c.setPosition(end, QTextCursor::KeepAnchor);
                c.removeSelectedText();
                c.movePosition(QTextCursor::StartOfLine);
                c.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
                QRegExp q("\\S+");
                if(q.indexIn(c.selectedText()) == -1) {
                    c.setPosition(c.position() + 1, QTextCursor::KeepAnchor);
                    c.removeSelectedText();
                }
            text->setTextCursor(c);
            return;
        }
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

void NotePad::onRefreshRequest()
{
    //emit un signal si le xml est valide
    QXmlStreamReader xml(text->toPlainText());
    hasError = false;

    while(!xml.atEnd()) {
        xml.readNext();
        if(xml.hasError())
        {
            hasError = true;
        }
    }

    if(!hasError)
    {
        updateDom();
        emit log("Xml valide", QColor("green"));
    }
    else
    {
        QTextCursor c = linesDisplay->textCursor();
        c.setPosition(0);
        c.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, xml.lineNumber() - 1);
        QTextBlockFormat b;
        b.setBackground(QColor("red"));
        c.setBlockFormat(b);
        linesDisplay->setTextCursor(c);

        c = text->textCursor();
        c.setPosition(0);
        c.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, xml.lineNumber() - 1);
        text->setTextCursor(c);
        text->ensureCursorVisible();

        emit log("Erreur ligne " + QString::number(xml.lineNumber()) + " : " + xml.errorString(), QColor("red"));
    }
}

void NotePad::onScroll(int y)
{
    linesDisplay->verticalScrollBar()->setValue(text->verticalScrollBar()->value());
}

void NotePad::updateNodeName(QDomNode n, QString oldName, QString newName)
{
    auto vequal = [](vector<int> v1, vector<int> v2)->bool
    {
            if(v1.size() == v2.size())
            {
                    for (int i = 0; i < v1.size(); ++i) {
                if(v2[i] != v1[i])
                {
                    return false;
                }
            }
            return true;
        }
        return false;
    };

    auto goToNodeStart = [] (int *begin, QString s)->void
    {
        QString open = "<";
        while(open.compare(s.at(*begin)) != 0)
        {
            (*begin)--;
        }
    };

    stack<int> st = ModeleXml::pathFromRoot(n);
    vector<int> nodePath;

    while(!st.empty())
    {
        nodePath.push_back(st.top());
        cout << "" << st.top() << endl;
        st.pop();
    }

    nodePath[0]++;
    vector<int> path;
    path.push_back(0);
    QXmlStreamReader xml(text->toPlainText());
    QXmlStreamReader::TokenType lastToken;
    lastToken = QXmlStreamReader::NoToken;
    QTextCursor c = text->textCursor();

    int begin;
    int end;
    int nbFound = 0;

    xml.readNext();
    while(!xml.atEnd()) {
        if(xml.isStartElement()) {
            if(lastToken == QXmlStreamReader::StartElement) {
                path.push_back(0);
            } else {
                path[path.size() - 1]++;
            }
        }

        else if(xml.isEndElement()) {
            if(lastToken == QXmlStreamReader::EndElement) {
                path.pop_back();
            }
        }

        if(vequal(path, nodePath))
        {
           if(nbFound == 0)
            {
                nbFound++;
                c.setPosition(0);
                c.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, xml.lineNumber()-1);
                c.setPosition(c.position() + xml.columnNumber() - oldName.size() - 2, QTextCursor::MoveAnchor);
                c.setPosition(c.position() + oldName.size() + 1, QTextCursor::KeepAnchor);
                begin = c.selectionStart();
                goToNodeStart(&begin, text->toPlainText());
                end = c.selectionEnd();

            }
            else if (nbFound == 1 && xml.name().size() > 0)
            {
                c.setPosition(0);
                c.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, xml.lineNumber()-1);
                c.setPosition(c.position() + xml.columnNumber() - oldName.size() - 2, QTextCursor::MoveAnchor);
                c.setPosition(c.position() + oldName.size() + 1, QTextCursor::KeepAnchor);

                QString t = c.selectedText();

                if(c.position() > end)
                {
                    t.replace(oldName, newName);
                    c.removeSelectedText();
                    c.insertText(t);
                }

                c.setPosition(begin);
                c.setPosition(end, QTextCursor::KeepAnchor);
                t = c.selectedText();
                t.replace(oldName, newName);
                c.removeSelectedText();
                c.insertText(t);

                text->setTextCursor(c);
                return;
            }
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

void NotePad::addLinesNumber()
{
    if(hasError)
    {
        int n = linesDisplay->document()->blockCount();
        linesDisplay->setText("1");
        for (int i = 0; i < n - 1; ++i) {
            linesDisplay->setAlignment(Qt::AlignRight);
            linesDisplay->append(QString::number(linesDisplay->document()->blockCount() + 1));
        }
    }
    while(linesDisplay->document()->blockCount() < text->document()->blockCount())
    {
        linesDisplay->setAlignment(Qt::AlignRight);
        linesDisplay->append(QString::number(linesDisplay->document()->blockCount() + 1));
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
