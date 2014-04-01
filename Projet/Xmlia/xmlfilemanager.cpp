#include "xmlfilemanager.h"

XmlFileManager::XmlFileManager()
{
}

void XmlFileManager::openFile(QString path)
{
    QDomDocument doc("document");
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)){
        // TODO Faire un critical
        cout<< "ERROR 1"<< endl;
    }
    QTextStream in(&file);
    content = in.readAll();
    cout << "content : " << content.toStdString() << endl;
    if (!doc.setContent(&file)) {
        // Todo faire un critical
        cout << "ERROR 2" << endl;
    }

    file.close();

    this->modele = new ModeleXml(&doc);

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
