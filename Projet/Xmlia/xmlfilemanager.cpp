#include "xmlfilemanager.h"

XmlFileManager::XmlFileManager()
{
    this->modele = new ModeleXml(new QDomDocument(""));
    isDtdActive = false;
}

void XmlFileManager::openFile()
{
    if(isDtdActive)
    {
        openDTD();
    }
    else
    {
        openXML();
    }
}

void XmlFileManager::openXML()
{
    QDomDocument *doc = new QDomDocument("");

    notepad->disableSchema();
    QString error;
    int errorLine;
    int errorColumn;

    QFile file(currentFile);

    if (!file.open(QIODevice::ReadOnly))
    {
        // TODO Faire un critical
        cout<< "ERROR 1"<< endl;
    }
    else
    {
        emit log("Opened file (XML) " + currentFile, QColor("gray"));
        QString data(file.readAll());

        if (!doc->setContent(data, &error, &errorLine, &errorColumn))
        {
            cout << "error : " << error.toStdString() << " at line " << errorLine << " at column " << errorColumn << endl;
            cout << "ERROR 2" << endl;
        }
        else
        {
            this->modele->setFromDocument(doc);
        }

        notepad->setText(data);
        file.close();

    }
}

void XmlFileManager::openDTD()
{
    if(currentDTD.size() > 1)
    {
        QFile file(currentDTD);

        if (!file.open(QIODevice::ReadOnly))
        {
            emit log("Linked Schema not found : " + currentDTD, QColor("red"));
        }
        else
        {
            QString data(file.readAll());
            notepad->setDtd(data);
            file.close();

            emit log("Opened file (DTD) " + currentDTD, QColor("gray"));
        }
    }
}

void XmlFileManager::genSchema()
{
    QString fileName(getCurrentFileName().split(".").first());
    currentDTD = getCurrentFilePath().append("/").append(fileName).append(".xsd");
    cout << "current dtd : " << currentDTD.toStdString() << endl;
    notepad->genSchema();
    saveSchema();
}

void XmlFileManager::saveFile(QString f, bool isDtd)
{
    QFile file(f);
    if (!file.open(QIODevice::WriteOnly))
    {
        // error message
    }
    else
    {
        QTextStream stream(&file);
        if(isDtd) {
            stream << notepad->getSchema();
        } else {
            stream << notepad->getXml();
        }
        stream.flush();
        file.close();
        emit log("Saved file under " + f, QColor("gray"));
    }
}

void XmlFileManager::saveSchema()
{
    saveFile(currentDTD, true);
}

void XmlFileManager::saveXml()
{
    saveFile(currentFile, false);
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

void XmlFileManager::setCurrentSchema(QString xsd)
{
    currentDTD = xsd;
    if(!notepad->hasSchema())
    {
        openDTD();
    }
}

QString XmlFileManager::getCurrentFile() const
{
    return (isDtdActive?currentDTD:currentFile);
}

QString XmlFileManager::getCurrentFilePath() const
{
    QStringList l = currentFile.split("/");
    l.removeLast();
    return l.join("/");
}

QString XmlFileManager::getCurrentSchema() const
{
    return currentDTD;
}

QString XmlFileManager::getCurrentFileName() const
{
    QString file = (isDtdActive?currentDTD:currentFile).split("/").back();
    return file;
}

QString XmlFileManager::getSchemaName() const
{
    return currentDTD.split("/").back();
}

QString XmlFileManager::getXmlName() const
{
    return currentFile.split("/").back();
}

void XmlFileManager::setActiveTab(bool isDtd)
{
    isDtdActive = isDtd;
}

void XmlFileManager::setNotePad(NotePad *notepad)
{
    this->notepad = notepad;
}
