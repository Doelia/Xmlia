#ifndef ARBO_H
#define ARBO_H

#include <QApplication>
#include <QWidget>
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

class Arbo : public QWidget
{
    Q_OBJECT

private:
    QTreeView* vue;
    ModeleXml* modele;

    /**
      * @action Remplit le modèle QStandardItemModel à partir d'un QDomNode dom
      *
      */
    void preOrder(QDomNode* dom, QStandardItemModel *model);

    QStandardItem* getFils(QDomNode dom);

public:

    Arbo();

    /**
     * @brief Arbo::getVue
     * @return Une nouvelle vue calculée à partir du modèle
     */
    QTreeView* getVue();

public slots:
    void updateView();



};

#endif // ARBO_H
