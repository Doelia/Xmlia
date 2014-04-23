#include "xmlfilemanager.h"

XmlFileManager::XmlFileManager()
{
    this->modele = new ModeleXml(new QDomDocument(""));
    isDtdActive = false;
}

void XmlFileManager::openFile(NotePad *n)
{
    if(isDtdActive)
    {
        openDTD(n);
    }
    else
    {
        openXML(n);
    }
}


void XmlFileManager::openXML(NotePad *n)
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

    emit log("Opened file (XML) " + currentFile, QColor("gray"));
}

void XmlFileManager::openDTD(NotePad *n)
{
    QFile file(currentDTD);

    if (!file.open(QIODevice::ReadOnly)){
        // TODO Faire un critical
        cout<< "ERROR 1"<< endl;
    }
    QString data(file.readAll());
    n->setDtd(data);
    file.close();

    emit log("Opened file (DTD) " + currentDTD, QColor("gray"));
}

void XmlFileManager::saveFile(NotePad *n)
{
    QFile file((isDtdActive?currentDTD:currentFile));
    if (!file.open(QIODevice::WriteOnly)) {
        // error message
    } else {
        QTextStream stream(&file);
        stream << n->getText();
        stream.flush();
        file.close();
        emit log("Saved file under " + (isDtdActive?currentDTD:currentFile), QColor("gray"));
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
    if(isDtdActive)
    {
        this->currentDTD = file;
    }
    else
    {
        this->currentFile = file;
    }
}

QString XmlFileManager::getCurrentFile() const
{
    return (isDtdActive?currentDTD:currentFile);
}

QString XmlFileManager::getCurrentFileName() const
{
    QString file = (isDtdActive?currentDTD:currentFile).split("/").back();
    return file;
}

void XmlFileManager::setActiveTab(bool isDtd)
{
    isDtdActive = isDtd;
}
