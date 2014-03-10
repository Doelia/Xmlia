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

#include "mainwindow.h"

using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();

}
