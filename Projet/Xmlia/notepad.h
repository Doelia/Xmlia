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

class CustomTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    CustomTabWidget();
    void disableDTD();
    void enableDTD();
private slots:
    void onShiftTabHit();
    void onTabHit();
    void onToggle();
    void onTabChanged();
private:
    bool isDtdEnabled;
};

class NotePad : public QWidget
{
    Q_OBJECT

public:
    NotePad();
    void indent();
    void setText(QString s);
    void setDtd(QString s);
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

signals:
    void update();
    void log(QString s, QColor c);

private:
    XmlEditor *xmlEditor;
    DtdEditor *dtdEditor;
    CustomTabWidget *view;

    QString getStringFromDom() const;

    void updateDom();
};


#endif // NOTEPAD_H
