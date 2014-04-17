#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QtGui>
//#include <QtWidgets>
#include <QtXml/QDomDocument>
#include <iostream>
#include <stack>
#include <QtXml/QXmlSimpleReader>
#include "xmlfilemanager.h"

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

public slots:
    void onNodeNameUpdate(QDomNode, QString);
    void onNodeDelete(QDomNode);

signals:
    void update();

private:
    int NB_SPACE = 8;

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

    void addCloseMarkup();

    int tabNumber;

    QDomNode currentNode() const;
    void changeTextFromNode(QDomNode node, QString oldName, QString newName, int childNumber);
};

#endif // NOTEPAD_H
