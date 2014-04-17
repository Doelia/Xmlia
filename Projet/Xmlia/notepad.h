#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QObject>
#include <QtGui>
//#include <QtWidgets>
#include <QtXml/QDomDocument>
#include <iostream>
#include <stack>
#include <QtXml/QXmlSimpleReader>
#include "QGridLayout"
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

    //QTextEdit *getTextEdit() const;

    QWidget* getView() const;

public slots:
    void onNodeNameUpdate(QDomNode, QString);
    void onNodeDelete(QDomNode);
    void onRefreshRequest();
    void toggleLoggerWindow();

private slots:
    void onScroll(int);
    void addLinesNumber();

signals:
    void update();

private:
    int NB_SPACE = 8;
    bool hasError;

    QTextEdit* text;
    QTextEdit* linesDisplay;
    QTextEdit* logger;

    QGridLayout* grid;

    QWidget* view;

    QXmlStreamReader* reader;
    TextHighLighter* th;
    int tabNumber;

    QString getStringFromDom() const;

    void updateDom();

    void keyPressEvent(QKeyEvent *e);
    bool eventFilter(QObject *o, QEvent *e);

    QString tabsString(int n) const;

    void indentLineWithBounds(QStringList *list, int line, int upperBound, int lowerBound);

    bool insertCharacterForKeyFiltering(const QString str);

    void addCloseMarkup();

    QDomNode currentNode() const;
    void updateNodeName(QDomNode node, QString oldName, QString newName);

    QDomNode nodeWithPositionFromNode(QDomNode) const;

};

#endif // NOTEPAD_H
