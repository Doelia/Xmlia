#ifndef MODELEXML_H
#define MODELEXML_H

/*===============================================
 * nom : modelexml.h         projet : xmlia
 * modele de données representant la structure
 * du document xml
 *=============================================*/

#include <QDomNode>
#include <QWidget>
#include <stack>
#include <QStandardItem>

class ModeleXml  : public QObject
{
    Q_OBJECT

private:
    QDomDocument* dom;
    static int rowFromNode(QDomNode n);

public:
    ModeleXml(QDomDocument* dom);
    virtual ~ModeleXml();

    QString domToString() const;
    QDomNode* getRacine() const;

    /**
      @action Met à jour le modèle à partir d'un texte XML
      @pr Texte valide
    */
    void update(QString s);

    /**
       @action Modifie le nom du noeud passé en parametre,
       et envoi le signal onNodeNameUpdate
    */
    void updateNodeName(QDomNode n, QString newName);

    /**
       @action Modifie le nom du noeud passé en parametre,
       et envoi le signal onNodeNameUpdate
    */
    void insertNode(QDomNode parent, QDomNode node);

    /**
      @action Supprime le noeud et sa sous arborescente
      et envoi le signal onNodeRemove
    */
    void removeNode(QDomNode dom);

    void aboutToBeRemoved(QDomNode);

    /**
      @action Affecte le modèle par le docuement passé en parametre
    */
    void setFromDocument(QDomDocument* doc);

    /**
      @return Un chemin à partir de la racine, numéroté par le numéro de chaque fis.
      Exemple: 0-1-2-0
    */
    static std::stack<int> pathFromRoot(QDomNode n);

    /**
      @return true si le node est égal à l'item (même fils)
    */
    static bool equals(QDomNode n, QStandardItem* i);


    /**
      @return le nombre de fils du node
    */
    static int childCount(QStandardItem* n);

    /**
        @return Le parent de l'item en trop non comprit dans dans le modèle XML
     */
    static QDomNode getParentOfExtraItem(QDomNode node, QStandardItem* root);


    static int countSumChild(QDomNode n);
    static int countSumChild(QStandardItem* n);

    QDomNode getSameNodeFromItem(QStandardItem* root);

    /**
     * @brief NodeFromPath
     * @return QDomNode got from the path
     */
    QDomNode nodeFromPath(std::vector<int>) const;

    /**
     * @return Un node vide si le node n'est pas là sinon le node correspondant à l'item
     */
    QDomNode getSameNodeFromItemRecursive(QDomNode node, QStandardItem* item) const;

    /**
     * @return La racine en QDomNode
     */
    QDomNode getNonPointerRoot() const;

signals:
    void onNodeNameUpdate(QDomNode n, QString newName);
    void onNodeDelete(QDomNode n);
    void onNodeInsert(QDomNode parent, QDomNode n);
    void onAboutToBeRemoved(QDomNode);

};

#endif // MODELEXML_H
