#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QtGui>
//#include <QtWidgets>
#include <QtXml/QDomDocument>
#include <iostream>
#include <stack>

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
    void insertTabs(QString* l, int n) const;

    stack<QString>* pile;

    bool isOpenTag(QString token) const;
    bool isCloseTag(QString token) const;

    int selectLineStart(QString s);
    int selectLineEnd(QString s);

    void selectWholeLine() const;

    void indent();

    bool insertCharacterForKeyFiltering(const QString str);

    void appendTextWithBounds(QString* indented, int upperBound, int lowerBound, int currentLine, QString toAppend);

};

#endif // NOTEPAD_H
