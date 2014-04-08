#include "arbo.h"
#include <string>
#include "xmlfilemanager.h"

using namespace std;


Arbo::Arbo()
{

}

QStandardItem* Arbo::getFils(QDomNode dom) {
    QStandardItem *item = new QStandardItem(dom.nodeName());
    for (int i = 0; i < dom.childNodes().size(); i++) {
        item->appendRow(this->getFils(dom.childNodes().at(i)));
    }
    return item;
}

/**
  * @action Remplit le modèle QStandardItemModel à partir d'un QDomNode dom
  * TODO Benoit
  *
  */
void Arbo::preOrder(QDomNode* dom, QStandardItemModel* model) {

  //  cout << dom->childNodes().at(0).localName().toStdString();

    model->setItem(0, getFils(*dom));
}


/**
 * @brief Arbo::getVue
 * @return Une nouvelle vue calculée à partir du modèle
 */

QTreeView* Arbo::getVue() {

    // Création de la vue
    vue = new QTreeView;
    this->updateView();
    return this->vue;
}

void Arbo::updateView() {

     // Construction du modèle arborescent vide
    QStandardItemModel *model = new QStandardItemModel();

    // Mise en ordre
    this->preOrder(XmlFileManager::getFileManager()->getModele()->getRacine(), model);

    vue->setModel(model);
}

