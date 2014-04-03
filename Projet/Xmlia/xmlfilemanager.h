#ifndef XMLFILEMANAGER_H
#define XMLFILEMANAGER_H

#include <QString>
#include <modelexml.h>
#include <QDomDocument>
#include <QFile>
#include <iostream>
#include <QTextStream>

/**
  * Permet de gérer les fichiers (enregistrement, ouverture...) et récupérer le dom
  *
  */

using namespace std;

class XmlFileManager
{
private:
    XmlFileManager();
    ModeleXml *modele;

public:
    /**
        Enregistre un modèle dans un fichier .xml
    */
    void saveInFile(ModeleXml* modele, QString path);

    /**
       Ouvre un fichier .xml et retourne son modèle
    */
    void openFile(QString path);

    ModeleXml *getModele() const;
    static XmlFileManager *getFileManager();
};


#endif // XMLFILEMANAGER_H
