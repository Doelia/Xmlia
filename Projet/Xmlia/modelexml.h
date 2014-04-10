#ifndef MODELEXML_H
#define MODELEXML_H

#include <QDomNode>
#include <QWidget>
#include <attribute.h>

class ModeleXml  : public QObject
{
    Q_OBJECT

private:
    QDomDocument* dom;

public:
    ModeleXml(QDomDocument* dom);
    virtual ~ModeleXml();
    void addNode(QDomNode, QDomNode);
    void removeNode(QDomNode dom);

    void addAttribut(QDomNode element, Attribute t);
    void removeAttribut(QDomNode element, Attribute t);
    QString domToString() const;
    QDomNode* getRacine() const;
    void update(QString s);

    /**
       Reconstruit le QDomDocument en modifiant le nom du noeud "dom"
       Stratégie : Parcourir et reconstruire un nouveau QDomDocument à partir de l'ancien, en recursif ou avec une pile,
       et detecter quand on atteint le bon dom en modifiant le nom
    */
    void updateNodeName(QDomNode n, QString newName);
    void setFromDocument(QDomDocument* doc);

signals:
    void onNodeNameUpdate(QDomNode n, QString newName);

};

#endif // MODELEXML_H
