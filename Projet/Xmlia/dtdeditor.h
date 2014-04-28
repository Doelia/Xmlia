#ifndef DTDEDITOR_H
#define DTDEDITOR_H

#include "texteditor.h"

class DtdEditor  : public TextEditor
{
public:
    DtdEditor();
    bool eventFilter(QObject *o, QEvent *e);
    void genSchema(QList<QString>);
};

#endif // DTDEDITOR_H
