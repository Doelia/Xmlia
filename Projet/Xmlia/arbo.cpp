#include "arbo.h"
#include <string>
#include "xmlfilemanager.h"
#include <stack>

using namespace std;


Arbo::Arbo() {
    this->vue = 0;
}

void Arbo::onEdit (QStandardItem* item) {

    QDomNode node = this->getNodeFromItem(item);
    cout << "Node modifié = " << node.nodeName().toStdString() << endl;

    XmlFileManager::getFileManager()->getModele()->updateNodeName(node, item->text());
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

QTreeView* Arbo::getVue() {
    // Création de la vue
    if (!this->vue) {
        vue = new QTreeView();
        this->updateView();
    }
    return this->vue;
}


void Arbo::updateView() {
     // Construction du modèle arborescent vide
    QStandardItemModel *model = new QStandardItemModel();

    // Mise en ordre
    this->preOrder(XmlFileManager::getFileManager()->getModele()->getRacine(), model);

    // Redéfinition du modèle
    vue->setModel(model);

}

