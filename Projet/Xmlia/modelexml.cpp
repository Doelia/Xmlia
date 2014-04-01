#include "modelexml.h"

ModeleXml::ModeleXml(QDomDocument* dom)
{
    this->dom = dom;
}

QDomNode *ModeleXml::getRacine() const
{
    return this->dom;
}

