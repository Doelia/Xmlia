#include "modelexml.h"
#include <iostream>
#include "xmlfilemanager.h"


ModeleXml::ModeleXml(QDomNode* dom)
{
    this->dom = dom;
}

QDomNode *ModeleXml::getRacine() const
{
    return this->dom;
}

QString ModeleXml::domToString() const
{
    //TODO changer ca
    return XmlFileManager::getFileManager()->content;
}

