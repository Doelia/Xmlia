#ifndef MODELEXML_H
#define MODELEXML_H

#include <QDomDocument>
#include <attribute.h>


class ModeleXml
{
private:
    QDomNode* dom;
public:
    ModeleXml(QDomNode* dom);
    void addNode(QDomNode* dom);
    void removeNode(QDomNode* dom);
    void addAttribut(QDomNode* element, Attribute t);
    void removeAttribut(QDomNode* element, Attribute t);
    QDomNode* getRacine() const;
};

#endif // MODELEXML_H
