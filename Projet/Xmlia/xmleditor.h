#ifndef XMLEDITOR_H
#define XMLEDITOR_H

#include <QTextEdit>
#include <QXmlStreamReader>
#include <QDomNode>
#include <vector>
#include <stack>
#include <QtXmlPatterns/QXmlSchemaValidator>
#include <QtXmlPatterns/QXmlSchema>

using namespace std;

#include "texteditor.h"

class XmlEditor : public TextEditor
{
    Q_OBJECT
public:
    XmlEditor();

    /**
     * @brief addDtd lie le schema au document
     */
    void addDtd();

    /**
     * @brief removeSchema supprime le lien au schema
     */
    void removeSchema();

    bool updateNodeName(int *nbFound, int *begin, int *end, QTextCursor *c, QString oldName, QString newName, QXmlStreamReader *xml);
    bool deleteNode(int *nbFound, int *begin, int *end, QTextCursor *c, QString oldName, QString newName, QXmlStreamReader *xml);
    bool saveNodeData(int *nbFound, int *begin, int *end, QTextCursor *c, QString oldName, QString newName, QXmlStreamReader *xml);
    bool insertNodeText(int *nbFound, int *begin, int *end, QTextCursor *c, QString oldName, QString newName, QXmlStreamReader *xml);

    void parseDom(QDomNode &target, QString oldName, QString newName, bool (XmlEditor::*function)
                  (int *nbFound, int *begin, int *end, QTextCursor *c, QString oldname, QString newname, QXmlStreamReader *xml));

    /**
     * @brief extractSchemaUrl
     * @return le lien vers le schema s'il existe
     */
    QString extractSchemaUrl();

    /**
      met à jour l'arbo et verifie si le xml est valide
      */
    bool validateAndRefreshTree();

    /**
     * @brief setSavedPath set le chemin vers le noeud deplace
     * @param path
     */
    void setSavedPath(stack<int> path);

private slots:
    void onTextChange();

signals:
    void update();

private:
    QString savedNodeData;
    stack<int> savedPath;


    bool eventFilter(QObject *o, QEvent *e);

    /**
     * @brief insertCharacterForKeyFiltering traite les caracters a filtrer au clavier
     * @param str
     * @return
     */
    bool insertCharacterForKeyFiltering(const QString str);

    /**
     * @brief updateDom met le modele a jour
     */
    void updateDom();

    /**
     * @brief goToNodeStart
     * @return la position du debut du node
     */
    int goToNodeStart(int, QString);

    /**
     * @brief cmpVectors
     * @return true si les deux vecteurs sont identiques
     */
    bool cmpVectors(vector<int>, vector<int>);

    /**
     * @brief moveCursorToLineAndColumn deplace le curseur c a la ligne line et la colonne column
     * @param c
     * @param line
     * @param column
     * @param keepAnchor
     */
    void moveCursorToLineAndColumn(QTextCursor* c, int line, int column, bool keepAnchor);

    /**
     * @brief addCloseMarkup ferme une balise
     */
    void addCloseMarkup();

};

#endif // XMLEDITOR_H
