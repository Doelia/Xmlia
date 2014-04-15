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
    cout << "ModeleXml::updateNodeName" << endl;
    //IMPORTANT : notifier tout le monde de changer avant de changer le modele
    emit onNodeNameUpdate(n, newName);
    cout << "ModeleXml::emitNodeNameUpdate()" << endl;
    if (n.isElement()) {
        n.toElement().setTagName(newName);
    }
}

void ModeleXml::setFromDocument(QDomDocument* doc)
{
    delete dom;
    this->dom = doc;
}

stack<int> ModeleXml::pathFromRoot(QDomNode n)
{
    stack<int> s;
    //s.push(0);

    while(!n.parentNode().isNull())
    {
        s.push(rowFromNode(n));
        n = n.parentNode();
    }

    return s;
}

int ModeleXml::rowFromNode(QDomNode n)
{
    int i = 0;
    while (n.parentNode().childNodes().at(i) != n)
    {
        i++;
    }
    return i;
}


void ModeleXml::removeNode(QDomNode dom)
{
    cout << "Remove " << dom.nodeName().toStdString() << endl;
}

QString ModeleXml::domToString() const
{
    return dom->toString();
}

