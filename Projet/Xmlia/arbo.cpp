#include "arbo.h"
#include <string>
#include "xmlfilemanager.h"
#include <stack>

using namespace std;


Arbo::Arbo() {
    this->vue = 0;
    this->blockSignals(true);
    this->model = new QStandardItemModel;

    connect(model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(onEdit(QStandardItem*)));
    connect(model, SIGNAL(rowsAboutToBeRemoved(const QModelIndex &, int, int)), this, SLOT(onRowsAboutToBeRemoved(QModelIndex,int,int)));
    connect(model, SIGNAL(rowsRemoved(const QModelIndex &, int, int)), this, SLOT(onRowsRemoved(const QModelIndex &, int, int)));
}

// Quand l'utilisateur édite ou ajoute un noeud
void Arbo::onEdit (QStandardItem* item) {

    if(item != this->itemRoot) {
        cout << "Arbo:: itemEdited : " << item->text().toStdString() << endl;
        QDomNode node = this->getNodeFromItem(item);

        if (    !node.isNull() &&
                ModeleXml::countSumChild(this->itemRoot) ==
                ModeleXml::countSumChild(*XmlFileManager::getFileManager()->getModele()->getRacine()) &&
                !node.isDocument())
        {
            cout << "Arbo:: Nom de node modifié par l'utilisateur = " << node.nodeName().toStdString() << endl;
            XmlFileManager::getFileManager()->getModele()->updateNodeName(node, item->text());
        } else { // C'est que c'est une insertion (drag n drop), l'item est en double

            if (item->parent()) {
                // Récupération du node où l'item a été inséré
                QDomNode parentInsert = this->getNodeFromItem(item->parent());
                cout << "Arbo::onEdit() : Node Parent : " << parentInsert.nodeName().toStdString() << endl;

                QDomNode same = XmlFileManager::getFileManager()->getModele()->getSameNodeFromItem(item);
                if (!same.isNull())
                {
                    same = same.cloneNode(true);
                    XmlFileManager::getFileManager()->getModele()->insertNode(parentInsert, same); // Modifcation du modèle
                }
                else
                {
                    //Cas bug à tester
                    cout << "Arbo::onEdit BUG : same est null" << endl;
                    updateView();
                }

            } else {
                //Quand on droppe un elem en tant que nouvelle racine
                cout << "Arbo::onEdit BUG : Parent non existant" << endl;
                updateView();
            }
        }
    }
    else {
        this->itemRoot->setText(XmlFileManager::getFileManager()->getCurrentFileName());
    }
}
// Quand l'utilisateur supprimer un noeud (clic droit)
void Arbo::onRemoveNode() {
    QStandardItem* item = this->itemRoot->model()->itemFromIndex(this->getVue()->selectionModel()->currentIndex());
    item->parent()->removeRow(item->row());
}

// Quand l'utilisatreur supprime un noeud par drag n drop
void Arbo::onRowsRemoved(const QModelIndex & i, int x, int y) {

    cout << "****************************" << endl;
    cout << "Arbo::onRemoved" << endl;
    cout << "****************************" << endl;

    QStandardItem* item = this->itemRoot->model()->itemFromIndex(i);
    QDomNode node = this->getNodeFromItem(item);
    if (!node.isNull())
    {
        node = node.childNodes().at(x);
        cout << "Arbo:: Node supprimé par utilisateur : " << node.nodeName().toStdString() << endl;
        XmlFileManager::getFileManager()->getModele()->removeNode(node); // Modifcation du modèle
    }
    else
    {
        cout << "Arbo::onRowsRemoved BUG : Le node à supprimer est nul" << endl;
        updateView();
    }
}

void Arbo::onRowsAboutToBeRemoved(const QModelIndex &i , int x, int y)
{
    cout << "****************************" << endl;
    cout << "Arbo::onRowsAboutToBeRemoved" << endl;
    cout << "****************************" << endl;
    QStandardItem* item = this->itemRoot->model()->itemFromIndex(i);
    QDomNode node = this->getNodeFromItem(item);
    node = node.childNodes().at(x);
    XmlFileManager::getFileManager()->getModele()->aboutToBeRemoved(node);
}


QStandardItem* Arbo::getItemFromNode(QDomNode dom) {
    stack<int> pile = XmlFileManager::getFileManager()->getModele()->pathFromRoot(dom);
    QStandardItem* item = this->itemRoot;
    while (!pile.empty()) {
        if (item && ModeleXml::childCount(item) > pile.top()) {
            item = item->child(pile.top());
            pile.pop();
        } else {
            return 0;
        }
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
    model->clear();
    this->itemRoot = getFils(dom);
    //On met le nom de nom de ficher comme nom de racine de l'arbo
    itemRoot->setText(XmlFileManager::getFileManager()->getCurrentFileName());

    model->setItem(0, this->itemRoot);
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

    QDomNode n = *XmlFileManager::getFileManager()->getModele()->getRacine(); // On apelle le constructeur
    //on enleve le type de noeud que l'on ne veut pas dans l'arbo
    removeNodeType(&QDomNode::isComment, &n);
    removeNodeType(&QDomNode::isText, &n);
    removeNodeType(&QDomNode::isProcessingInstruction, &n);

    // Construction du modèle arborescent vide

    // Mise en ordre
    this->preOrder(n, model);
    // this->setHeaderItem();

    // Redéfinition du modèle
    vue->setModel(model);
}
