#include <QApplication>
#include <QtGui>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDirModel>
#include <QTreeView>
#include <QFile>
#include <QDomDocument>
#include <QStandardItemModel>

#include <iostream>

#include "mainwindow.h"
#include "xmlfilemanager.h"
#include "modelexml.h"
#include "arbo.h"

using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Chargement d'un fichier XML
    /*XmlFileManager* fm = new XmlFileManager();
    ModeleXml* modele = fm->openFile("/home/doelia/Documents/xmlia/Tests/Arbo/test.xml");*/

    // Création de la vue arborescente en passant le pointeur vers le modèle
    Arbo* arbo = new Arbo();
    NotePad *notePad = new NotePad();

    // Fenetre principale
    MainWindow window;

    // Envoi de la vue arborescente à la fenetre
    window.setArbo(arbo);
    window.setNotePad(notePad);

    // Affichage et execution
    window.show();
    return app.exec();

}
