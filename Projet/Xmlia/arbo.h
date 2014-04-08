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
#include <QTextStream>
#include <iostream>

#include "modelexml.h"

using namespace std;

class Arbo : public QTreeWidget
{

    Q_OBJECT

public slots:

    void onEdit (QTreeWidgetItem * item, int column);

private:
    QTreeView* vue;
    ModeleXml* modele;

    /**
      * @action Remplit le modèle QStandardItemModel à partir d'un QDomNode dom
      *
      */
    void preOrder(QDomNode* dom, QStandardItemModel *model);

    /**
     * @brief Arbo::getFils
     * @param dom
     * @return Un item remplit avec les fils du dom
     * Méthode récusrive
     */
    QStandardItem* getFils(QDomNode dom);

public:

    Arbo();

    /**
     * @brief Arbo::getVue
     * @return Génére une vue et la retourne
     */
    QTreeView* getVue();

    /**
     * @brief Arbo::updateView
     * @action Met à jour la vue à partir du modèle
     */
    void updateView();

};

#endif // ARBO_H
