#include "dtdeditor.h"

DtdEditor::DtdEditor() : TextEditor::TextEditor(new TextHighLighter(0))
{
    this->text->installEventFilter(this);
    QStringList l;
    l << "element" << "attribute" << "schema"
      << "complexType" << "sequence" << "name"
      << "string" << "positiveInteger" << "decimal"
      << "minOccurs" << "maxOccurs" << "unbounded"
      << "required" << "version" << "encoding";
    completer = new QCompleter(l);
}

bool DtdEditor::eventFilter(QObject *o, QEvent *e)
{

    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(e);

    if (e->type() == QEvent::KeyPress)
    {
        emit cursorInfo(text->textCursor().block().blockNumber(), text->textCursor().positionInBlock());
        if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Right || keyEvent->key() == Qt::Key_Tab)
        {
            cout << textUnderCursor().toStdString() << endl;

            return insertCompletion();
        }
        else
        {
            if(keyEvent->key() == Qt::Key_Backspace)
            {
                removeCompletion();
            }
        }
    }
    else if (e->type() == 199)
    {
        emit cursorInfo(text->textCursor().block().blockNumber(), text->textCursor().positionInBlock());
    }
    return false;
}

void DtdEditor::genSchema(QList<QString> l)
{
    text->setText("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>");
    text->append("<xs:schema xmlns:xs=\"http://www.w3.org/2001/XMLSchema\">");
    l.removeFirst();

    for(QString s : l)
    {
        QString toAppend("<xs:element name=\"");
        toAppend.append(s).append("\"/>");
        text->append(toAppend);
    }
    text->append("</xs:schema>");
    indent();
}
