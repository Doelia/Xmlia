#include "notepad.h"

NotePad::NotePad()
{
    this->text = new QTextEdit();
    this->th = new TextHighLighter(text->document());
    this->reader = new QXmlStreamReader();

    this->text->installEventFilter(this);

    this->tabNumber = 0;
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
            return insertCharacterForKeyFiltering(">");
        }
        else if (keyEvent->key() == Qt::Key_Tab)
        {
            this->currentNode();
            return true;
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

QString NotePad::getStringFromDom() const
{
    this->text->setText(XmlFileManager::getFileManager()->getModele()->domToString());
}

void NotePad::updateDom()
{
    /*QXmlStreamReader xml(this->text->toPlainText());
    QDomNode dom;

    while(!xml.atEnd())
    {
        xml.readNext();

        if(xml.isStartElement())
        {

            cout << xml.name().toString().toStdString() << endl;
        }
        else if(xml.isEndElement())
        {

        }
    }*/
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
    QString left = text->toPlainText().left(pos);
    QString right = text->toPlainText().right(text->toPlainText().length() - pos);

    QString s = left.append(str).append(right);

    text->setPlainText(s);
    c.setPosition(pos + 1);
    text->setTextCursor(c);
    this->indent();
    return true;
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
        l.append("        ");
    }
    return l;
}
