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
    this->dom->setContent(s);
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

void ModeleXml::removeNode(QDomNode n) {
    emit onNodeDelete(n);
    cout << "ModeleXml:: Remove " << n.nodeName().toStdString() << endl;
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


bool ModeleXml::equals(QDomNode n, QStandardItem* i)
{
    if (n.nodeName().compare(i->text())) {
        return false;
    } else {
        return true;
    }
}

int ModeleXml::childCount(QStandardItem* item)
{
    int i = 0;
    while (item->child(i))
    {
        i++;
    }
    return i;
}

// Un item a été inséré, on cherche dans quel parent
QDomNode ModeleXml::getParentOfExtraItem(QDomNode node, QStandardItem* root)
{
    QDomNode nullNode;
    nullNode.clear();

    if (node.childNodes().length() == 0) {
        return nullNode;
    } else {
        if (node.childNodes().length() >= childCount(root)) {
            for (int i=0; i < node.childNodes().length(); i++) {
                QDomNode n = getParentOfExtraItem(node.childNodes().at(i), root->child(i));
                if (!n.isNull()) {
                    return n;
                }
            }
            return nullNode;
        } else { // Un item de plus que de node, c'est qu'il a été inséré ici
            return node;
        }
    }
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

