#include "arbo.h"
#include <string>
#include "xmlfilemanager.h"

using namespace std;


Arbo::Arbo()
{

}

/**
  * @action Remplit le modèle QStandardItemModel à partir d'un QDomNode dom
  * TODO Benoit
  *
  */
void Arbo::preOrder(QDomNode* dom, QStandardItemModel* model) {

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


/**
 * @brief Arbo::getVue
 * @return Une nouvelle vue calculée à partir du modèle
 */

QTreeView* Arbo::getVue() {

    // Construction du modèle arborescent vide
    QStandardItemModel *model = new QStandardItemModel();

    // Mise en ordre
    this->preOrder(XmlFileManager::getFileManager()->getModele()->getRacine(), model);

    // Création de la vue
    vue = new QTreeView;
    vue->setModel(model);

    return this->vue;
}

