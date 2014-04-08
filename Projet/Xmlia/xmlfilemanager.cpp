#include "xmlfilemanager.h"

XmlFileManager::XmlFileManager()
{
    this->modele = new ModeleXml(new QDomDocument(""));
}

void XmlFileManager::openFile(QString path)
{
    delete(this->modele);
    cout << "freed !" << endl;

    QDomDocument *doc = new QDomDocument("document");

    QString error;
    int errorLine;
    int errorColumn;

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)){
        // TODO Faire un critical
        cout<< "ERROR 1"<< endl;
    }

    if (!doc->setContent(&file, &error, &errorLine, &errorColumn)) {
        cout << "error : " << error.toStdString() << " at line " << errorLine << " at column " << errorColumn << endl;
        cout << "ERROR 2" << endl;
    }

    file.close();

    this->modele = new ModeleXml(doc);
}

ModeleXml *XmlFileManager::getModele() const
{
    return this->modele;
}

XmlFileManager *XmlFileManager::getFileManager()
{
    static XmlFileManager *manager = new XmlFileManager();
    return manager;
}
