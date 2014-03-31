#ifndef NOTEPAD_H
#define NOTEPAD_H

//#include <QtGui>
#include <QtWidgets>
#include <QtXml/QDomDocument>
#include <iostream>
#include <stack>
#include <QtXml/QXmlSimpleReader>

using namespace std;

#include "texthighlighter.h"

class NotePad : public QMainWindow
{
    Q_OBJECT

public:
    NotePad();

signals:

private slots:
    void quit();
    void open();
    void save();
    void toRed();
    void toGreen();
    void toBlack();
    void onTextChange();
    void onIndent();
    void parse();

private:
    QTextEdit* text;

    QAction* openAction;
    QAction* saveAction;
    QAction* exitAction;
    QAction* changeColorAction;
    QAction* toRedAction;
    QAction* toGreenAction;
    QAction* toBlackAction;
    QAction* textChangedAction;
    QAction* indentAction;

    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* changeColorMenu;
    QMenu* toRedMenu;
    QMenu* toGreenMenu;
    QMenu* toBlackMenu;

    QDomDocument* xml;
    QXmlStreamReader* reader;

    TextHighLighter* th;

    void keyPressEvent(QKeyEvent *e);
    bool eventFilter(QObject *o, QEvent *e);

    void insertTabsOnEnterHit() const;
    QString tabsString(int n) const;

    void selectWholeLine() const;

    void indent();
    void indentLineWithBounds(QStringList *list, int line, int upperBound, int lowerBound);

    bool insertCharacterForKeyFiltering(const QString str);

    int tabNumber;

};

#endif // NOTEPAD_H
