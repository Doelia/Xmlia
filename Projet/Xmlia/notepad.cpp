#include "notepad.h"
#include "xmlfilemanager.h"

NotePad::NotePad()
{
    this->xmlEditor = new XmlEditor();
    this->dtdEditor = new DtdEditor();
    this->view = new CustomTabWidget();

    view->addTab(xmlEditor->getView(), "Xml");
    view->addTab(dtdEditor->getView(), "");

    view->disableDTD();

    connect(xmlEditor, SIGNAL(log(QString,QColor)), this, SLOT(onLog(QString,QColor)));
    connect(xmlEditor, SIGNAL(update()), this, SLOT(onUpdate()));
    connect(xmlEditor, SIGNAL(cursorInfo(int,int)), this, SLOT(onCursorInfo(int,int)));
    connect(dtdEditor, SIGNAL(cursorInfo(int,int)), this, SLOT(onCursorInfo(int,int)));
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

void NotePad::setDtd(QString s)
{
    dtdEditor->setText(s);
    view->enableDTD();
    xmlEditor->addDtd();
}

QString NotePad::getXml() const
{
    /**
      retourner le texte de l'onglet actif ?
      */
    return xmlEditor->getText();
}

QString NotePad::getSchema() const
{
    return dtdEditor->getText();
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

void NotePad::onNodeInsert(QDomNode parent, QDomNode n)
{
    xmlEditor->onNodeInsert(parent, n);
}

void NotePad::onRefreshRequest()
{
    xmlEditor->onRefreshRequest();
}

void NotePad::onLog(QString s, QColor c)
{
    emit log(s, c);
}

void NotePad::onUpdate()
{
    emit update();
}

void NotePad::onCursorInfo(int line, int column)
{
    emit cursorInfo(line, column);
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


CustomTabWidget::CustomTabWidget() : QTabWidget::QTabWidget()
{
    isDtdEnabled = false;
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Tab), this, SLOT(onTabHit()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_Tab), this, SLOT(onShiftTabHit()));
    new QShortcut(QKeySequence(Qt::Key_F4), this, SLOT(onToggle()));
    connect(this, SIGNAL(currentChanged(int)), this, SLOT(onTabChanged()));
}

void CustomTabWidget::disableDTD()
{
    isDtdEnabled = false;
    this->setTabIcon(1, QIcon::fromTheme("document-open"));
    this->setTabText(1, "Ajouter une DTD");
}

void CustomTabWidget::enableDTD()
{
    isDtdEnabled = true;
    this->setTabIcon(1, QIcon(""));
    this->setTabText(1, "DTD");
}

void CustomTabWidget::onTabHit()
{
    if(isDtdEnabled)
    {
        this->setCurrentIndex(1);
    }
}

void CustomTabWidget::onShiftTabHit()
{
    this->setCurrentIndex(this->currentIndex() - 1);
}

void CustomTabWidget::onToggle()
{
    if(currentIndex() == 0)
    {
        if(isDtdEnabled)
        {
            this->setCurrentIndex(1);
        }
    }
    else
    {
        setCurrentIndex(0);
    }
}

void CustomTabWidget::onTabChanged()
{
    enableDTD();
    XmlFileManager::getFileManager()->setActiveTab(currentIndex());
}
