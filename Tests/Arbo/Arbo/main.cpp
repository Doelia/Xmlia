#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDirModel>
#include <QTreeView>
#include <QFile>
#include <QDomDocument>
#include <QStandardItemModel>

#include <iostream>

#include "arbo.h"
#include "fenetre.h"

using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Fenetre fenetre;
    fenetre.show();

    return app.exec();

}
