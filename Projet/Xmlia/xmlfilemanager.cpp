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

        emit log("Opened file (XML) " + currentFile, QColor("gray"));
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

void XmlFileManager::saveFile()
{
    QFile file((isDtdActive?currentDTD:currentFile));
    if (!file.open(QIODevice::WriteOnly))
    {
        // error message
    }
    else
    {
        QTextStream stream(&file);
        if(isDtdActive) {
            stream << notepad->getSchema();
        } else {
            stream << notepad->getXml();
        }
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

void XmlFileManager::setActiveTab(bool isDtd)
{
    isDtdActive = isDtd;
}

void XmlFileManager::setNotePad(NotePad *notepad)
{
    this->notepad = notepad;
}
