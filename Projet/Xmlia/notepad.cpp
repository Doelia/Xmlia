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
    c.setPosition(selectionEnd);
    int lowerBound = c.blockNumber();

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
            last = xml.lineNumber();
            indentLineWithBounds(&line, xml.lineNumber() - 1, upperBound, lowerBound);
            tabNumber++;
        }
        else if(token == QXmlStreamReader::EndElement)
        {
            last = xml.lineNumber();
            tabNumber--;
            indentLineWithBounds(&line, xml.lineNumber() - 1, upperBound, lowerBound);
        }
    }

    if(selectionStart < s.length() - 1)
    {
        text->setPlainText(line.join("\n"));
    }
    c.setPosition(selectionEnd);
    c.movePosition(QTextCursor::EndOfBlock);
    text->setTextCursor(c);
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

QString NotePad::tabsString(int n) const
{
    QString l;
    for (int i = 0; i < n; i++) {
        l.append("        ");
    }
    return l;
}

void NotePad::insertTabsOnEnterHit() const
{
    this->text->textCursor().insertText("\n");

    for (int i = 0; i < tabNumber; ++i) {
        this->text->textCursor().insertText("    ");
    }
}
