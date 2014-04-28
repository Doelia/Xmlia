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
    bool isDtdEnabled() const;
private slots:
    void onShiftTabHit();
    void onTabHit();
    void onToggle();
    void onTabChanged();
private:
    bool dtdEnabled;
};

class NotePad : public QWidget
{
    Q_OBJECT

public:
    NotePad();
    void indent();
    void setText(QString s);
    void setDtd(QString s);
    QString getXml() const;
    QString getSchema() const;
    bool hasSchema() const;
    void genSchema();
    void loadSchema();
    void disableSchema();
    void deleteSchema();
    bool isDtdEnabled() const;

    //QTextEdit *getTextEdit() const;

    QWidget* getView() const;

public slots:
    void onNodeNameUpdate(QDomNode, QString);
    void onNodeDelete(QDomNode);
    void onNodeInsert(QDomNode parent, QDomNode n);
    void onAboutToBeRemoved(QDomNode);

    /**
      met à jour l'arbo et verifie si le xml est valide
      */
    void onRefreshRequest();

private slots:
    void onLog(QString, QColor);
    void onUpdate();
    void onCursorInfo(int, int);

signals:
    void update();
    void log(QString s, QColor c);
    void cursorInfo(int, int);

private:
    XmlEditor *xmlEditor;
    DtdEditor *dtdEditor;
    CustomTabWidget *view;

    bool dragndropHappened;
    stack<int> savedPath;

    QString getStringFromDom() const;

    void updateDom();

    /**
     * @brief isPathGreater
     * @return true if s1 is greater than s2
     */
    bool isPathGreater(stack<int> s1, stack<int> s2) const;
};


#endif // NOTEPAD_H
