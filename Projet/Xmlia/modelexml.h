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
     void modifyNodeName(QDomNode dom, QString s);
    void addAttribut(QDomNode element, Attribute t);
    void removeAttribut(QDomNode element, Attribute t);
    QString domToString() const;
    QDomNode* getRacine() const;
    void update(QString s);
};

#endif // MODELEXML_H
