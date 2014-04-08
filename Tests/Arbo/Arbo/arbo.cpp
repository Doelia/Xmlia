#include "arbo.h"
#include <string>

using namespace std;

/**
  * @action Remplit le modèle QStandardItemModel à partir d'un QDomNode dom
  * TODO Benoit
  *
  */
void Arbo::preOrder(QDomNode dom, QStandardItemModel *model) {

      // Exemple de création d'item
    QStandardItem *item1 = new QStandardItem("Item 1");
    QStandardItem *item11 = new QStandardItem("Item 1.1");
    QStandardItem *item111 = new QStandardItem("Item 1.1.1");
    QStandardItem *item12 = new QStandardItem("Item 1.2");

    // Exemple de laison entre les items
    item1->appendRow(item11);
    item11->appendRow(item111);
    item1->appendRow(item12);

    // Ajout d'un item au modèle
    model->setItem(0, item1);
}

QTreeView* Arbo::getVue() const {
    return this->vue;
}

Arbo::Arbo()
{

    // TODO : QDomDocument à récupérer ailleurs
    QDomDocument doc("mydocument");
    QFile file("//home/doelia/Documents/xmlia/Tests/Arbo/test.xml"); // TODO récupérer en relatif...
    if (!file.open(QIODevice::ReadOnly)) {
        cout << "ERROR 1"<< endl;
        return;
    }
    if (!doc.setContent(&file)) {
        cout << "ERROR 2" << endl;
        file.close();
        return;
    }
    file.close();

    // Chargement du modèle
    QStandardItemModel *model = new QStandardItemModel();
    this->preOrder(doc, model);

    vue = new QTreeView;
    vue->setModel(model);

}
