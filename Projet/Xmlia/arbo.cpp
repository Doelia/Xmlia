#include "arbo.h"
#include <string>
#include "xmlfilemanager.h"

using namespace std;


Arbo::Arbo() {
}

void Arbo::onEdit (QModelIndex item) {
    cout << "coucou" << endl;
}

QStandardItem* Arbo::getFils(QDomNode dom) {
    QStandardItem *item = new QStandardItem(dom.nodeName());
    for (int i = 0; i < dom.childNodes().size(); i++) {
        item->appendRow(this->getFils(dom.childNodes().at(i)));
    }
    return item;
}

void Arbo::preOrder(QDomNode* dom, QStandardItemModel* model) {
    model->setItem(0, getFils(*dom));
}

QTreeView* Arbo::getVue() {
    // Création de la vue
    if (this->vue == NULL) {
        vue = new QTreeView;
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

     connect(this->vue->selectionModel(), SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(onEdit(QModelIndex)));
}

