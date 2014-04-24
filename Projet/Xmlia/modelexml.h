#ifndef MODELEXML_H
#define MODELEXML_H

#include <QDomNode>
#include <QWidget>
#include <attribute.h>
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
      Provisoir, mise à jour du modèle à partir d'un text
    */
    void update(QString s);

    /**
       Modifie le nom du noeud passé en parametre,
       et envoi le signal onNodeNameUpdate
    */
    void updateNodeName(QDomNode n, QString newName);

    /**
      Supprime le noeud et sa sous arborescente
      et envoi le signal onNodeRemove
    */
    void removeNode(QDomNode dom);

    /**
      Affecte le modèle par le docuement passé en parametre
    */
    void setFromDocument(QDomDocument* doc);

    /**
      Retourne un chemin à partir de la racine, numéroté par le numéro de chaque fis.
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
        Compare le node et l'item et retourne le node qui n'existe pas, null si se sont les même
     */
    static QDomNode getParentOfExtraItem(QDomNode node, QStandardItem* root);

    /**
     * @brief NodeFromPath
     * @return QDomNode got from the path
     */
    QDomNode nodeFromPath(std::vector<int>) const;

signals:
    void onNodeNameUpdate(QDomNode n, QString newName);
    void onNodeDelete(QDomNode n);

};

#endif // MODELEXML_H
