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
    cout << "Arbo:: Node modifié par l'utilisateur = " << node.nodeName().toStdString() << endl;

    XmlFileManager::getFileManager()->getModele()->updateNodeName(node, item->text());
}


// Quand l'utilisateur supprimer un noeud
void Arbo::onRemoveNove() {
    QStandardItem* item = this->itemRoot->model()->itemFromIndex(this->getVue()->selectionModel()->currentIndex());
    cout << "Arbo:: Node supprimé par l'utilisateur : " << item->text().toStdString() << endl;
    QDomNode node = this->getNodeFromItem(item);
    XmlFileManager::getFileManager()->getModele()->removeNode(node);
}


// Quand le modèle est modifié
void Arbo::onNodeDelete(QDomNode n)
 {
       QStandardItem* itemRemoved =  this->getItemFromNode(n);
       itemRemoved->parent()->removeRow(itemRemoved->row());
 }


QStandardItem* Arbo::getItemFromNode(QDomNode dom) {
    stack<int> pile = XmlFileManager::getFileManager()->getModele()->pathFromRoot(dom);
    QStandardItem* item = this->itemRoot;
    while (!pile.empty()) {
        item = item->child(pile.top());
        pile.pop();
    }
    return item;
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

// Met a jour la vue à partir du modèle
void Arbo::updateView() {
     // Construction du modèle arborescent vide
    QStandardItemModel *model = new QStandardItemModel();

    // Mise en ordre
    this->preOrder(XmlFileManager::getFileManager()->getModele()->getRacine(), model);

    // Redéfinition du modèle
    vue->setModel(model);

}
