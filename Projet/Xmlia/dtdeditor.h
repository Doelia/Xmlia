#ifndef DTDEDITOR_H
#define DTDEDITOR_H

#include "texteditor.h"

class DtdEditor  : public TextEditor
{
public:
    DtdEditor();
    bool eventFilter(QObject *o, QEvent *e);
};

#endif // DTDEDITOR_H
