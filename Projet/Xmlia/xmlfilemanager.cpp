

#include "xmlfilemanager.h"

XmlFileManager::XmlFileManager()
{
}

ModeleXml* XmlFileManager::openFile(QString path)
{
    QDomDocument doc("document");
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)){
        // TODO Faire un critical
        cout<< "ERROR 1"<< endl;
    }
    if (!doc.setContent(&file)) {
        // Todo faire un critical
        cout << "ERROR 2" << endl;
    }
    file.close();

    return new ModeleXml(&doc);

}
