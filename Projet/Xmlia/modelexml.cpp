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
    cout << dom->childNodes().at(1).childNodes().at(0).nodeValue().toStdString() << endl;
}

void ModeleXml::updateNodeName(QDomNode n, QString newName)
{
    cout << "ModeleXml::updateNodeName() : emit" << endl;
    emit onNodeNameUpdate(n, newName);

    // Mise à jour du modèle
    if (n.isElement()) {
        n.toElement().setTagName(newName);
    }

    cout << "ModeleXml::updateNodeName() : Modèle MAJ OK" << endl;
}

int ModeleXml::countSumChild(QDomNode n)
{
    if (n.childNodes().length() == 0)
    {
        return 0;
    }
    else
    {
        int s = 0;
        for (int i = 0; i < n.childNodes().length(); i++)
        {
            s += 1 + countSumChild(n.childNodes().at(i));
        }
        return s;
    }
}

int ModeleXml::countSumChild(QStandardItem* n)
{
    if (childCount(n) == 0)
    {
        return 0;
    }
    else
    {
        int s = 0;
        for (int i = 0; i < childCount(n); i++)
        {
            s += 1+ countSumChild(n->child(i));
        }
        return s;
    }
}

void ModeleXml::insertNode(QDomNode parent, QDomNode node)
{
    cout << "ModeleXml::insertNode() : " << node.nodeName().toStdString() << " in " <<  parent.nodeName().toStdString() << endl;
    emit onNodeInsert(parent, node);
    //parent.insertBefore(node, parent.firstChild());
    parent.appendChild(node);
}

void ModeleXml::removeNode(QDomNode n) {
    cout << "ModeleXml:: Remove " << n.nodeName().toStdString() << endl;
    emit onNodeDelete(n);
    n.parentNode().removeChild(n);
    cout << "ModeleXml::removeNode() : Modèle MAJ OK" << endl;
}

void ModeleXml::aboutToBeRemoved(QDomNode n)
{
    cout << "ModelXml::aboutToBeRemoved" << endl;
    emit onAboutToBeRemoved(n);
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
    if (n.nodeName().compare(i->text()))
    {
        return false;
    }
    else
    {
        QDomNodeList children = n.childNodes();
        if (children.count() != i->rowCount())
        {
            return false;
        }
        else
        {
            int n = 0;
            while (n < children.count() && equals(children.at(n), i->child(n)))
            {
                n++;
            }
            return (n == children.count());
        }
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

    if (node.childNodes().length() == 0)
    {
        return nullNode;
    }
    else
    {
        if (node.childNodes().length() >= childCount(root))
        {
            for (int i=0; i < node.childNodes().length(); i++)
            {
                QDomNode n = getParentOfExtraItem(node.childNodes().at(i), root->child(i));
                if (!n.isNull())
                {
                    return n;
                }
            }
            return nullNode;
        }
        else
        { // Un item de plus que de node, c'est qu'il a été inséré ici
            return node;
        }
    }
}

QDomNode ModeleXml::getSameNodeFromItem(QStandardItem* root)
{
    return getSameNodeFromItemRecursive(getNonPointerRoot(), root);
}

QDomNode ModeleXml::getSameNodeFromItemRecursive(QDomNode node, QStandardItem* item) const
{
    if (equals(node, item))
    {
        return node;
    }
    else
    {
        int i = 0;
        QDomNode tmp;
        while (i < node.childNodes().count() && (tmp = getSameNodeFromItemRecursive(node.childNodes().at(i), item)).isNull())
        {
            i++;
        }
        if (i == node.childNodes().count())
        {
            QDomNode nullNode;
            nullNode.clear();
            return nullNode;
        }
        else
        {
            return tmp;
        }
    }
}

QDomNode ModeleXml::nodeFromPath(std::vector<int> path) const
{
    QDomNode n = *this->dom;

    for (int var = 0; var < path.size(); ++var)
    {
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

QDomNode ModeleXml::getNonPointerRoot() const
{
    return *dom;
}
