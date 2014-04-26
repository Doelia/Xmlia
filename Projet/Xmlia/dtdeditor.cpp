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
    emit cursorInfo(text->textCursor().block().blockNumber(), text->textCursor().positionInBlock());

    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(e);

    if (e->type() == QEvent::KeyPress)
    {
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
    return false;
}
