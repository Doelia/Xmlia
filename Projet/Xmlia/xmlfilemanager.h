#ifndef XMLFILEMANAGER_H
#define XMLFILEMANAGER_H

#include <QString>
#include <modelexml.h>
#include <QDomDocument>
#include <QFile>
#include <iostream>


/**
  * Permet de gérer les fichiers (enregistrement, ouverture...) et récupérer le dom
  *
  */

using namespace std;

class XmlFileManager
{
public:
    XmlFileManager();

    /**
        Enregistre un modèle dans un fichier .xml
    */
    void saveInFile(ModeleXml* modele, QString path);

    /**
       Ouvre un fichier .xml et retourne son modèle
    */
    ModeleXml* openFile(QString path);
};

#endif // XMLFILEMANAGER_H
