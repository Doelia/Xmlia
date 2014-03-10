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
    QStandardItem* item;
    int nRow;
public:
    Arbo();
    void preOrder(QDomNode dom, QStandardItemModel *model);
    void insertFather(QString name);
    void insertChildren(QString name);
    void setItem(QStandardItemModel *model);
};

#endif // ARBO_H
