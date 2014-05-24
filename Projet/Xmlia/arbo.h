#ifndef ARBO_H
#define ARBO_H

#include <QApplication>
#include <QTreeWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDirModel>
#include <QTreeView>
#include <QFile>
#include <QDomDocument>
#include <QStandardItemModel>
#include <QString>
#include <QAction>
#include <QTextStream>
#include <iostream>
#include <QHeaderView>
#include <stack>
#include <string>

#include "modelexml.h"
#include "xmlfilemanager.h"


using namespace std;

class Arbo : public QTreeWidget
{

    Q_OBJECT

public slots:

    /**
     * @action Met à jour entièrement la vue à partir du modèle
     */
    void updateView();

    /**
     * @on Executé quand l'utilisateur modifie le nom d'un noeud, ou effectue une insertion par un drop
     * @param QStandardItem l'item modifié
     */
    void onEdit (QStandardItem*);

    /**
     * @on Executé quand l'utilisateur supprime un noeud
     */
    void onRemoveNode();

    /** 
     * @on Executé quand un noeud est supprimé par le drag n drop
     */ 
    void onRowsRemoved(const QModelIndex &, int, int);


    /**
     * @on Executé avant qu'un noeud soit supprimé du modèle
     */
    void onRowsAboutToBeRemoved(const QModelIndex &, int, int);

private:

    QTreeView* vue; // Vue du widget
    ModeleXml* modele; // Vue du modèle XML
    QStandardItem* itemRoot; // Pointeur vers l'item racine de l'arborescence
    QStandardItemModel *model; // Pointeur vers l'item père du modèle

    /**
      * @action Remplit le modèle QStandardItemModel à partir d'un QDomNode dom
      * @param dom la racine deu dom
      * @param model le modèle vide à remplir
      */
    void preOrder(QDomNode dom, QStandardItemModel *model);

    /**
     * @brief Arbo::getFils
     * @param dom
     * @return Un item remplit avec les fils du dom
     * Méthode récursive nécessaire au preOrder
     */
    QStandardItem* getFils(QDomNode dom);

    /*** Conversions item/modèle **/
    QStandardItem* getItemFromNode(QDomNode dom);
    QDomNode getNodeFromItem(QStandardItem* item);

public:

    Arbo();

    /**
     * @brief Arbo::getVue
     * @return Génére une vue si elle n'existe pas encore, et la retourne
     */
    QTreeView* getVue();


};

#endif // ARBO_H
