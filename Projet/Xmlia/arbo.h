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

#include "modelexml.h"

using namespace std;

class Arbo : public QTreeWidget
{

    Q_OBJECT

public slots:

    /**
     * @brief Arbo::updateView
     * @action Met à jour la vue à partir du modèle
     * Met a jour la vue à partir du modèle, à faire qu'au début du programme
     */
    void updateView();


    /***** Action envoyés par l'utilisateur, à retourner au modèle  *******/

    /** Quand l'utilisateur modifie le nom d'un noeud */
    void onEdit (QStandardItem*);
    /** Quand l'utilisateur supprime un noeud */
    void onRemoveNove();
    /**********************************************************************/

    /**** Action envoyé par le modèle, modifs à appliquer à l'arbre *******/
    void onNodeNameUpdate(QDomNode, QString);
    /**********************************************************************/


private:
    QTreeView* vue;
    ModeleXml* modele;
    QStandardItem* itemRoot;

    /**
      * @action Remplit le modèle QStandardItemModel à partir d'un QDomNode dom
      *
      */
    void preOrder(QDomNode* dom, QStandardItemModel *model);

    /**
     * @brief Arbo::getFils
     * @param dom
     * @return Un item remplit avec les fils du dom
     * Méthode récusrive nécessaire au preOrder
     */
    QStandardItem* getFils(QDomNode dom);


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
