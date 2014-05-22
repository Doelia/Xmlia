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
    /**
     * @brief disableDTD desactive l'onglet schema
     */
    void disableDTD();

    /**
     * @brief enableDTD active l'onglet schema
     */
    void enableDTD();

    /**
     * @brief isDtdEnabled
     * @return true si l'onglet schema est active
     */
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
    /**
     * @brief indent indente le texte
     */
    void indent();

    /**
     * @brief setText set le texte de l'editeur xml avec s
     * @param s
     */
    void setText(QString s);

    /**
     * @brief setDtd set le texte de l'editeur schema avec s
     * @param s
     */
    void setDtd(QString s);

    /**
     * @brief getXml
     * @return le contenu de l'editeur xml
     */
    QString getXml() const;

    /**
     * @brief getSchema
     * @return le contenu de l'editeur schema
     */
    QString getSchema() const;

    /**
     * @brief hasSchema
     * @return si l'editeur schema a un schema
     */
    bool hasSchema() const;

    /**
     * @brief genSchema genere un schema en fonction des elements present dans l'editeur xml
     * l'ajoute dans l'editeur schema
     * lie le document xml au schema genere
     */
    void genSchema();

    /**
     * @brief loadSchema charge un schema dans l'editeur schema et le lie au document xml
     */
    void loadSchema();

    /**
     * @brief disableSchema desactive l'onglet schema
     */
    void disableSchema();

    /**
     * @brief deleteSchema supprime le lien du document xml vers le schema
     */
    void deleteSchema();

    /**
     * @brief isDtdEnabled
     * @return true si un schema est actif
     */
    bool isDtdEnabled() const;

    /**
     * @brief getView
     * @return le widget pour l'affichage
     */
    QWidget* getView() const;

public slots:
    /**
     * @brief onNodeNameUpdate change le nom du node n en s
     * @param n
     * @param s
     */
    void onNodeNameUpdate(QDomNode n, QString s);

    /**
     * @brief onNodeDelete supprime le node n
     * @param n
     */
    void onNodeDelete(QDomNode n);

    /**
     * @brief onNodeInsert sauvegarde l'emplacement du parent
     * @param parent
     * @param n
     */
    void onNodeInsert(QDomNode parent, QDomNode n);

    /**
     * @brief onAboutToBeRemoved sauvegarde les donnees du node n
     */
    void onAboutToBeRemoved(QDomNode n);

    /**
     * @brief validateAndRefreshTree valide le document xml et met a jour l'arbo s'il est valide
     */
    void validateAndRefreshTree();

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

    void addCompletion();

    /**
     * @brief isPathGreater
     * @return true if s1 is greater than s2
     */
    bool isPathGreater(stack<int> s1, stack<int> s2) const;
};


#endif // NOTEPAD_H
