#include "modelexml.h"

ModeleXml::ModeleXml(QDomDocument* dom)
{
    this->dom = dom;
}

QDomDocument *ModeleXml::getRacine() const
{
    return this->dom;
}

