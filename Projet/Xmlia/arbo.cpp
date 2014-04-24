#include "arbo.h"
#include <string>
#include "xmlfilemanager.h"
#include <stack>

using namespace std;


Arbo::Arbo() {
    this->vue = 0;
    this->blockSignals(true);
}

// Quand l'utilisateur édite ou ajoute un noeud
void Arbo::onEdit (QStandardItem* item) {

    if(item != this->itemRoot) {
        cout << "Arbo:: itemEdited : " << item->text().toStdString() << endl;
        QDomNode node = this->getNodeFromItem(item);
        cout << "Arbo:: Node modifié par l'utilisateur = " << node.nodeName().toStdString() << endl;

        if (!node.isNull()) {
            XmlFileManager::getFileManager()->getModele()->updateNodeName(node, item->text());
         } else { // C'est que c'est une insertion (drag n drop), l'item est en double

            // Récupération du node où l'item a été inséré
            QDomNode parentInsert = this->getNodeFromItem(item->parent());

            cout << "Item Parent : " << item->parent()->text().toStdString() << endl;
             cout << "Node Parent : " << parentInsert.nodeName().toStdString() << endl;

            //QDomNode same = getSameNodeFromItem(item);

            //XmlFileManager::getFileManager()->insertNode(parentInsert, )->


        }
    }
    else {
        this->itemRoot->setText(XmlFileManager::getFileManager()->getCurrentFileName());
    }
}



// Quand l'utilisateur supprimer un noeud
void Arbo::onRemoveNode() {
    QStandardItem* item = this->itemRoot->model()->itemFromIndex(this->getVue()->selectionModel()->currentIndex());
    cout << "Arbo:: Node supprimé par l'utilisateur : " << item->text().toStdString() << endl;
    QDomNode node = this->getNodeFromItem(item);
    XmlFileManager::getFileManager()->getModele()->removeNode(node);
}

// Quand l'utilisatreur supprime un noeud par drag n drop
void Arbo::onRowsRemoved(const QModelIndex & i, int x, int y) {
    QStandardItem* item = this->itemRoot->model()->itemFromIndex(i);
    item = item->child(x);
    cout << "Arbo:: Node supprimé par drag n drop : " << item->text().toStdString() << endl;
    QDomNode node = this->getNodeFromItem(item);
    XmlFileManager::getFileManager()->getModele()->removeNode(node);
}


// Quand le modèle est modifié
void Arbo::onNodeDelete(QDomNode n) {
    QStandardItem* itemRemoved =  this->getItemFromNode(n);
    cout << "Arbo : Demande de suppression de l'item " << itemRemoved->text().toStdString() << " par le modèle " << endl;
    //itemRemoved->parent()->removeRow(itemRemoved->row());
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

void Arbo::preOrder(QDomNode dom, QStandardItemModel* model) {
    this->itemRoot = getFils(dom);
    //On met le nom de nom de ficher comme nom de racine de l'arbo
    itemRoot->setText(XmlFileManager::getFileManager()->getCurrentFileName());

    model->setItem(0, this->itemRoot);
    connect(model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(onEdit(QStandardItem*)));
    connect(model, SIGNAL(rowsRemoved(const QModelIndex &, int, int)), this, SLOT(onRowsRemoved(const QModelIndex &, int, int)));
}

// Retourne la vue, la crée si elle nexiste pas
QTreeView* Arbo::getVue() {
    // Création de la vue
    if (!this->vue) {
        vue = new QTreeView();
        vue->header()->hide();
        vue->setContextMenuPolicy(Qt::ActionsContextMenu);
        QAction* rmove = new QAction("Supprimer le noeud", vue);
        vue->addAction(rmove);
        connect(rmove, SIGNAL(triggered()), this, SLOT(onRemoveNode()));
        vue->setDragEnabled(true);
        vue->setAcceptDrops(true);
        vue->setDragDropMode(QAbstractItemView::InternalMove);
        this->updateView();

    }
    return this->vue;
}

// Met a jour la vue à partir du modèle
void Arbo::updateView() {

    /**
      fonction qui enleve un certain type de noeud identifé par le predicat 'function'
      */
    std::function<void (bool (QDomNode::*function)() const, QDomNode *dom)> removeNodeType;
    removeNodeType = [&removeNodeType] (bool (QDomNode::*function)() const, QDomNode *dom)
    {
        for (int var = 0; var < dom->childNodes().size(); ++var) {
            QDomNode n = dom->childNodes().at(var);
            if((n.*function)())
            {
                dom->removeChild(n);
            }
            else
            {
                removeNodeType(function, &n);
            }
        }
    };

    QDomNode n(*XmlFileManager::getFileManager()->getModele()->getRacine()); // On apelle le constructeur
    //on enleve le type de noeud que l'on ne veut pas dans l'arbo
    removeNodeType(&QDomNode::isComment, &n);
    removeNodeType(&QDomNode::isText, &n);
    removeNodeType(&QDomNode::isProcessingInstruction, &n);

    // Construction du modèle arborescent vide
    QStandardItemModel *model = new QStandardItemModel();

    // Mise en ordre
    this->preOrder(n, model);
   // this->setHeaderItem();

    // Redéfinition du modèle
    vue->setModel(model);
}
