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
private:
    QTreeView* vue;
    ModeleXml* modele;
public:

    Arbo();

    /**
     * @brief Arbo::getVue
     * @return Une nouvelle vue calculée à partir du modèle
     */
    QTreeView* getVue();


    /**
      * @action Remplit le modèle QStandardItemModel à partir d'un QDomNode dom
      *
      */
    void preOrder(QDomNode* dom, QStandardItemModel *model);
};

#endif // ARBO_H
