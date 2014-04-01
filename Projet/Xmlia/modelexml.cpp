#include "modelexml.h"

ModeleXml::ModeleXml(QDomNode* dom)
{
    this->dom = dom;
}

QDomNode *ModeleXml::getRacine() const
{
    return this->dom;
}

