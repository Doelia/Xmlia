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
    NotePad *notepad;

    QString currentFile;
    QString currentDTD;
    bool isDtdActive;

signals:
    void log(QString s, QColor c);

public:
    /**
        Enregistre le modèle dans un fichier .xml
    */
    void saveFile(QString file, bool isDtd);

    void saveSchema();
    void saveXml();

    /**
        Construit le modèle à partir d'un fichier
    */
    void openFile();
    void openXML();
    void openDTD();

    /**
      genere et sauvegarde un schema xsd du meme nom que le fichier xml ouvert
      */
    void genSchema();

    ModeleXml *getModele() const;
    static XmlFileManager *getFileManager();

    /**
      set le ficher courant
      */
    void setCurrentFile(QString file);

    /**
      set le schema courant et notifie les editeurs de texte
      */
    void setCurrentSchema(QString xsd);

    /**
      @return le nom complet avec le chemin du ficher courant
      */
    QString getCurrentFile() const;

    /**
     * @brief getCurrentFilePath
     * @return le path vers le fichier xml chargé
     */

    QString getCurrentFilePath() const;

    /**
      @return le nom complet avec le chemin du schema xml
      */
    QString getCurrentSchema() const;

    /**
      @return le nom du ficher sans le path
      */
    QString getCurrentFileName() const;

    /**
      set l'onglet actif
      0 : editeur xml
      1 : editeur schema
      */
    void setActiveTab(bool isDtd);

    void setNotePad(NotePad *notepad);
};


#endif // XMLFILEMANAGER_H
