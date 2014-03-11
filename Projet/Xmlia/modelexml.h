#ifndef MODELEXML_H
#define MODELEXML_H

#include <QDomDocument>
#include <attribute.h>


class ModeleXml
{
private:
    QDomDocument* dom;
public:
    ModeleXml(QDomDocument* dom);
    void addNode(QDomDocument* dom);
    void removeNode(QDomDocument* dom);
    void addAttribut(QDomDocument* element, Attribute t);
    void removeAttribut(QDomDocument* element, Attribute t);
};

#endif // MODELEXML_H
