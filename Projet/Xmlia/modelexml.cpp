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

    // Mise à jour du modèle
    if (n.isElement()) {
        n.toElement().setTagName(newName);
    }
}

void ModeleXml::removeNode(QDomNode n)
{
    emit onNodeDelete(n);

    cout << "Remove " << n.nodeName().toStdString() << endl;

    n.parentNode().removeChild(n);
}


void ModeleXml::setFromDocument(QDomDocument* doc)
{
    delete dom;
    this->dom = doc;
}

stack<int> ModeleXml::pathFromRoot(QDomNode n)
{
    stack<int> s;
    while(!n.parentNode().isNull())
    {
        s.push(rowFromNode(n));
        n = n.parentNode();
    }

    return s;
}

QDomNode ModeleXml::nodeFromPath(std::vector<int> path) const
{
    QDomNode n = *this->dom;

    for (int var = 0; var < path.size(); ++var) {
        n = n.childNodes().at(path[var]);
    }
    return n;
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

QString ModeleXml::domToString() const
{
    return dom->toString();
}

