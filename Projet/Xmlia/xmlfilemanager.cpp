#include "xmlfilemanager.h"

XmlFileManager::XmlFileManager()
{
    this->modele = new ModeleXml(new QDomDocument(""));
}

void XmlFileManager::openFile(NotePad *n)
{
    QDomDocument *doc = new QDomDocument("");

    QString error;
    int errorLine;
    int errorColumn;

    QFile file(currentFile);

    if (!file.open(QIODevice::ReadOnly)){
        // TODO Faire un critical
        cout<< "ERROR 1"<< endl;
    }
    QString data(file.readAll());

    if (!doc->setContent(data, &error, &errorLine, &errorColumn)) {
        cout << "error : " << error.toStdString() << " at line " << errorLine << " at column " << errorColumn << endl;
        cout << "ERROR 2" << endl;
    }
    else
    {
        this->modele->setFromDocument(doc);
    }

    n->setText(data);
    file.close();

    emit log("Opened file " + currentFile, QColor("gray"));
}

void XmlFileManager::saveFile(NotePad *n)
{
    QFile file(currentFile);
    if (!file.open(QIODevice::WriteOnly)) {
        // error message
    } else {
        QTextStream stream(&file);
        stream << n->getText();
        stream.flush();
        file.close();
        emit log("Saved file under " + currentFile, QColor("gray"));
    }

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

void XmlFileManager::setCurrentFile(QString file)
{
    this->currentFile = file;
}

QString XmlFileManager::getCurrentFile() const
{
    return currentFile;
}

QString XmlFileManager::getCurrentFileName() const
{
    QString file = currentFile.split("/").back();
    return file;
}
