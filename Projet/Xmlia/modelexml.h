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
    void addNode(QDomNode* dom);
    void removeNode(QDomNode* dom);
    void addAttribut(QDomNode* element, Attribute t);
    void removeAttribut(QDomNode* element, Attribute t);
    QString domToString() const;
    QDomNode* getRacine() const;
};

#endif // MODELEXML_H
