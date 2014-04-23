#include "notepad.h"
#include "xmlfilemanager.h"

NotePad::NotePad()
{
    this->xmlEditor = new XmlEditor();
    this->dtdEditor = new DtdEditor();
    this->view = new QTabWidget();

    view->addTab(xmlEditor->getView(), "Xml");
    view->addTab(dtdEditor->getView(), "DTD");

    connect(xmlEditor, SIGNAL(log(QString,QColor)), this, SLOT(onLog(QString,QColor)));

}

void NotePad::indent()
{
    /**
      appeler le indent du XMlEditor
      */
    xmlEditor->indent();

}

void NotePad::setText(QString s)
{
    xmlEditor->setText(s);
}

QString NotePad::getText() const
{
    /**
      retourner le texte de l'onglet actif ?
      */
    return xmlEditor->getText();
}

QWidget *NotePad::getView() const
{
    return view;
}

void NotePad::onNodeNameUpdate(QDomNode n, QString newName)
{
    xmlEditor->onNodeNameUpdate(n, newName);
}

void NotePad::onNodeDelete(QDomNode n)
{
    xmlEditor->onNodeDelete(n);
}

void NotePad::onRefreshRequest()
{
    xmlEditor->onRefreshRequest();
}

void NotePad::onLog(QString s, QColor c)
{
    emit log(s, c);
}

QString NotePad::getStringFromDom() const
{
    xmlEditor->setText(XmlFileManager::getFileManager()->getModele()->domToString());
}

void NotePad::updateDom()
{
    XmlFileManager::getFileManager()->getModele()->update(xmlEditor->getText());
    emit update();
}

