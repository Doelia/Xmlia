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

using namespace std;

class Arbo : public QWidget
{
private:
    QTreeView* vue;
public:
    Arbo();
    QTreeView* getVue() const;
    void preOrder(QDomNode dom, QStandardItemModel *model);
};

#endif // ARBO_H
