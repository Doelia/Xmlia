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
#include <QScrollBar>
#include <QTabWidget>

#include "texthighlighter.h"
#include "modelexml.h"
#include <xmleditor.h>
#include <dtdeditor.h>

class NotePad : public QWidget
{
    Q_OBJECT

public:
    NotePad();
    void indent();
    void setText(QString s);
    QString getText() const;

    //QTextEdit *getTextEdit() const;

    QWidget* getView() const;

public slots:
    void onNodeNameUpdate(QDomNode, QString);
    void onNodeDelete(QDomNode);

    /**
      met à jour l'arbo et verifie si le xml est valide
      */
    void onRefreshRequest();

private slots:
    void onLog(QString, QColor);
    void onUpdate();
    /*void onScroll(int);
    void addLinesNumber();*/

signals:
    void update();
    void log(QString s, QColor c);

private:
    XmlEditor *xmlEditor;
    DtdEditor *dtdEditor;
    QTabWidget *view;

    QString getStringFromDom() const;

    void updateDom();
};

#endif // NOTEPAD_H
