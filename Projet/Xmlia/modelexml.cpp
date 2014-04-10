#include "modelexml.h"
#include <iostream>
#include "xmlfilemanager.h"


ModeleXml::ModeleXml(QDomDocument* dom)
{
    this->dom = dom;
}

ModeleXml::~ModeleXml()
{
    cout << "deleting ModeleXml" << endl;
    delete this->dom;
}


QDomNode* ModeleXml::getRacine() const
{
    return this->dom;
}

void ModeleXml::update(QString s)
{
    cout << "update" << endl;
    this->dom->setContent(s);
    cout << dom->childNodes().count() << endl;
}

void ModeleXml::updateNodeName(QDomNode n, QString newName)
{
    cout << "ModeleXml::emitNodeNameUpdate()" << endl;
    if (n.isElement()) {
        n.toElement().setTagName(newName);
    }
    emit onNodeNameUpdate(n, newName);
}

void ModeleXml::setFromDocument(QDomDocument* doc)
{
   delete dom;
   this->dom = doc;
}


void ModeleXml::removeNode(QDomNode dom)
{

}

QString ModeleXml::domToString() const
{
    return dom->toString();
}
