#include "arbo.h"
#include <string>
#include "xmlfilemanager.h"
#include <stack>

using namespace std;


Arbo::Arbo() {
    this->vue = 0;
}

// Quand l'utilisateur édite un noeud
void Arbo::onEdit (QStandardItem* item) {

    QDomNode node = this->getNodeFromItem(item);
    cout << "Node modifié par l'utilisateur = " << node.nodeName().toStdString() << endl;

    XmlFileManager::getFileManager()->getModele()->updateNodeName(node, item->text());
}


// Quand l'utilisateur supprimer un noeud
void Arbo::onRemoveNove() {
    QStandardItem* item = this->itemRoot->model()->itemFromIndex(this->getVue()->selectionModel()->currentIndex());
    cout << "Node supprimé par l'utilisateur : " << item->text().toStdString() << endl;

    QDomNode node = this->getNodeFromItem(item);

    XmlFileManager::getFileManager()->getModele()->removeNode(node);
}


// Quand le modèle est modifié, on modifie la vue
// TODO
void Arbo::onNodeNameUpdate(QDomNode, QString)
{
    cout << "Le modèle demande à modifier l'arbre" << endl;
}

QStandardItem* Arbo::getItemFromNode(QDomNode dom) {

}

// Pré requis: L'arboresecende de QDomNode est la même que celle de QStandardItem, sauf le nom qui change
QDomNode Arbo::getNodeFromItem(QStandardItem* item) {

    QDomNode curentNode = *(XmlFileManager::getFileManager()->getModele()->getRacine());

    stack<int> pile;

    pile.push(item->row());
    while (item->parent()) {
        item = item->parent();
         pile.push(item->row());
    }

     pile.pop();
    while (!pile.empty()) {
        curentNode = curentNode.childNodes().at(pile.top());
        pile.pop();
    }

    return curentNode;
}

// Fonction récursive nécessaire au preOrder
QStandardItem* Arbo::getFils(QDomNode dom) {
    QStandardItem *item = new QStandardItem(dom.nodeName());

    for (int i = 0; i < dom.childNodes().size(); i++) {
        item->appendRow(this->getFils(dom.childNodes().at(i)));
    }
    return item;
}

void Arbo::preOrder(QDomNode* dom, QStandardItemModel* model) {
    this->itemRoot = getFils(*dom);
    model->setItem(0, this->itemRoot);
     connect(model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(onEdit(QStandardItem*)));
}


// Retourne la vue, la crée si elle nexiste pas
QTreeView* Arbo::getVue() {
    // Création de la vue
    if (!this->vue) {
        vue = new QTreeView();
        vue->setContextMenuPolicy(Qt::ActionsContextMenu);
        QAction* rmove = new QAction("Supprimer le noeud", vue);
        vue->addAction(rmove);
        connect(rmove, SIGNAL(triggered()), this, SLOT(onRemoveNove()));
        this->updateView();
    }
    return this->vue;
}


// Met a jour la vue à partir du modèle, à faire qu'au début du programme
void Arbo::updateView() {
     // Construction du modèle arborescent vide
    QStandardItemModel *model = new QStandardItemModel();

    // Mise en ordre
    this->preOrder(XmlFileManager::getFileManager()->getModele()->getRacine(), model);

    // Redéfinition du modèle
    vue->setModel(model);

}

