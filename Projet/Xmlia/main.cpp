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

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Création de la vue arborescente en passant le pointeur vers le modèle
    cout << endl << "creation de Arbo" << endl;
    Arbo* arbo = new Arbo();
    cout << "Arbo creee" << endl;
    cout << "creation de l'editeur de texte" << endl;
    NotePad *notePad = new NotePad();
    cout << "editeur de texte cree" << endl;

    IconBar *iconbar = new IconBar();
    Logger *logger = new Logger();

    cout << "creation du file manager" << endl;
    XmlFileManager::getFileManager();
    cout << "file manager cree" << endl;

    // Fenetre principale
    cout << "creation de la fenetre principale" << endl;
    MainWindow window;
    cout << "fenetre principale creee" << endl;

    // Envoi de la vue arborescente à la fenetre
    cout << "ajout de Arbo dans la fenetre principale" << endl;
    window.setArbo(arbo);
    cout << "arbo ajoutee" << endl;
    cout << "ajout de l'editeur de texte dans la fenetre principale" << endl;
    window.setNotePad(notePad);
    cout << "editeur de texte ajoute" << endl;
    window.setIconBar(iconbar);
    window.setLogger(logger);

    // Affichage et execution
    window.show();
    return app.exec();

}
