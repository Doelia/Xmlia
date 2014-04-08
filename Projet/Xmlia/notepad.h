#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QtGui>
//#include <QtWidgets>
#include <QtXml/QDomDocument>
#include <iostream>
#include <stack>
#include <QtXml/QXmlSimpleReader>
#include "xmlfilemanager.h"

using namespace std;

#include "texthighlighter.h"
#include "modelexml.h"

class NotePad : public QWidget
{
    Q_OBJECT

public:
    NotePad();
    void indent();
    void setText(QString s);

    QTextEdit *getTextEdit() const;

signals:
    void update();

private:
    QTextEdit* text;
    QXmlStreamReader* reader;
    TextHighLighter* th;

    QString getStringFromDom() const;

    void updateDom();

    void keyPressEvent(QKeyEvent *e);
    bool eventFilter(QObject *o, QEvent *e);

    QString tabsString(int n) const;

    void indentLineWithBounds(QStringList *list, int line, int upperBound, int lowerBound);

    bool insertCharacterForKeyFiltering(const QString str);

    int tabNumber;

    QString currentNode() const;
};

#endif // NOTEPAD_H
