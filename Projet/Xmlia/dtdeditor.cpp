#include "dtdeditor.h"

DtdEditor::DtdEditor() : TextEditor::TextEditor(new TextHighLighter(0))
{
    this->text->installEventFilter(this);
}

bool DtdEditor::eventFilter(QObject *o, QEvent *e)
{
    emit cursorInfo(text->textCursor().block().blockNumber(), text->textCursor().positionInBlock());
}
