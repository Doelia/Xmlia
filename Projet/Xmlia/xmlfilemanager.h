#ifndef XMLFILEMANAGER_H
#define XMLFILEMANAGER_H

#include <QString>
#include <modelexml.h>
#include <QDomDocument>
#include <QFile>
#include <iostream>
#include <QTextStream>
#include <QFileDialog>
#include <QObject>
#include "notepad.h"

/**
  * Permet de gérer les fichiers (enregistrement, ouverture...) et récupérer le dom
  *
  */

using namespace std;

class XmlFileManager : public QObject
{
    Q_OBJECT

private:
    XmlFileManager();
    ModeleXml *modele;

    QString currentFile;

signals:
    void log(QString s, QColor c);

public:
    /**
        Enregistre le modèle dans un fichier .xml
    */
    void saveFile(NotePad *n);

    /**
        Construit le modèle à partir d'un fichier
    */
    void openFile(NotePad *n);


    ModeleXml *getModele() const;
    static XmlFileManager *getFileManager();

    /**
      set le ficher courant
      */
    void setCurrentFile(QString file);

    /**
      @return le nom complet avec le chemin du ficher courant
      */
    QString getCurrentFile() const;

    /**
      @return le nom du ficher sans le path
      */
    QString getCurrentFileName() const;
};


#endif // XMLFILEMANAGER_H
