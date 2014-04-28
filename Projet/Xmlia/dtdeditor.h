#ifndef DTDEDITOR_H
#define DTDEDITOR_H

#include "texteditor.h"

class DtdEditor  : public TextEditor
{
public:
    DtdEditor();
    bool eventFilter(QObject *o, QEvent *e);

    /**
     * @brief genSchema genere le schema xsd en fonction des elements
     * deja presents dans le fichier xml
     */
    void genSchema(QList<QString>);
};

#endif // DTDEDITOR_H
