#ifndef MODELEXML_H
#define MODELEXML_H

#include <QDomNode>
#include <attribute.h>

class ModeleXml
{
private:
    QDomDocument* dom;
public:
    ModeleXml(QDomDocument* dom);
    virtual ~ModeleXml();
    void addNode(QDomNode, QDomNode);
    void removeNode(QDomNode dom);

    /**
       Reconstruit le QDomDocument en modifiant le nom du noeud "dom"
       Stratégie : Parcourir et reconstruire un nouveau QDomDocument à partir de l'ancien, en recursif ou avec une pile,
       et detecter quand on atteint le bon dom en modifiant le nom
    */
     void modifyNodeName(QDomNode dom, QString newName);


    void addAttribut(QDomNode element, Attribute t);
    void removeAttribut(QDomNode element, Attribute t);
    QString domToString() const;
    QDomNode* getRacine() const;
    void update(QString s);
};

#endif // MODELEXML_H
