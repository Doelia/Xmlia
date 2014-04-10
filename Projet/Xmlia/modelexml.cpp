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

QString ModeleXml::domToString() const
{
    return dom->toString();
}


// TODO, voir .H
void ModeleXml::modifyNodeName(QDomNode nodeModify, QString s)
{

}

//
void ModeleXml::removeNode(QDomNode dom)
{

}

