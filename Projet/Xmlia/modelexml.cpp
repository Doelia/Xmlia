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

QDomNode *ModeleXml::getRacine() const
{
    return this->dom;
}

QString ModeleXml::domToString() const
{
    return dom->toString();
}

