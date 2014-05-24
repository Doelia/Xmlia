/*===============================================
 * nom : notepad.cpp         projet : xmlia
 *=============================================*/

#include "notepad.h"
#include "xmlfilemanager.h"

NotePad::NotePad()
{
    this->xmlEditor = new XmlEditor();
    this->schemaEditor = new DtdEditor();
    this->view = new CustomTabWidget();

    view->addTab(xmlEditor->getView(), "Xml");
    view->addTab(schemaEditor->getView(), "Schema");
    view->setTabEnabled(1, false);
    view->disableSchema();

    dragndropHappened = false;

    connect(xmlEditor, SIGNAL(log(QString,QColor)), this, SLOT(onLog(QString,QColor)));
    connect(xmlEditor, SIGNAL(update()), this, SLOT(onUpdate()));
    connect(xmlEditor, SIGNAL(cursorInfo(int,int)), this, SLOT(onCursorInfo(int,int)));
    connect(schemaEditor, SIGNAL(cursorInfo(int,int)), this, SLOT(onCursorInfo(int,int)));
}

void NotePad::indent()
{

    if(view->currentIndex())
    {
        schemaEditor->indent();
    }
    else
    {
        xmlEditor->indent();
    }
}

void NotePad::setText(QString s)
{
    xmlEditor->setText(s);
    xmlEditor->validateAndRefreshTree();
}

void NotePad::setDtd(QString s)
{
    schemaEditor->setText(s);
    view->enableDTD();
    addCompletion();
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
    return schemaEditor->getText();
}

bool NotePad::hasSchema() const
{
    return (schemaEditor->getText().size() > 1);
}

void NotePad::genSchema()
{
    QHash <QString, int> h;
    QXmlStreamReader xml(xmlEditor->getText());

    while(!xml.atEnd())
    {
        h.insert(xml.name().toString(), 0);
        xml.readNext();
    }
    xmlEditor->addDtd();
    schemaEditor->genSchema(h.keys());
    view->enableDTD();
}

void NotePad::loadSchema()
{
    xmlEditor->addDtd();
}

void NotePad::disableSchema()
{
    view->disableSchema();
}

void NotePad::deleteSchema()
{
    view->disableSchema();
    xmlEditor->removeSchema();
}

bool NotePad::isDtdEnabled() const
{
    return view->isDtdEnabled();
}

QWidget *NotePad::getView() const
{
    return view;
}

void NotePad::onNodeNameUpdate(QDomNode n, QString newName)
{
    xmlEditor->parseDom(n, n.nodeName(), QString(newName), &XmlEditor::updateNodeName);
}

void NotePad::onNodeDelete(QDomNode n)
{
    if(dragndropHappened)
    {
        dragndropHappened = false;
        if(isPathGreater(savedPath, ModeleXml::pathFromRoot(n)))
        {
            //cout << "is greater" << endl;
            xmlEditor->setSavedPath(savedPath);
            xmlEditor->parseDom(n, n.nodeName(), QString(""), &XmlEditor::insertNodeText);
            xmlEditor->parseDom(n, n.nodeName(), QString(""), &XmlEditor::deleteNode);
        }
        else
        {
            cout << "is lower" << endl;
            xmlEditor->parseDom(n, n.nodeName(), QString(""), &XmlEditor::deleteNode);
            xmlEditor->setSavedPath(savedPath);
            xmlEditor->parseDom(n, n.nodeName(), QString(""), &XmlEditor::insertNodeText);
        }
    }
    else
    {
        xmlEditor->parseDom(n, n.nodeName(), QString(""), &XmlEditor::deleteNode);
    }
    //xmlEditor->onNodeDelete(n);
}

void NotePad::onNodeInsert(QDomNode parent, QDomNode n)
{
    dragndropHappened = true;
    savedPath = ModeleXml::pathFromRoot(parent);
}

void NotePad::onAboutToBeRemoved(QDomNode n)
{
    xmlEditor->parseDom(n, n.nodeName(), QString(""), &XmlEditor::saveNodeData);
    //xmlEditor->saveNodeData(n);
}

void NotePad::validateAndRefreshTree()
{
    if(xmlEditor->validateAndRefreshTree())
    {
        view->enableDTD();
    }
    addCompletion();
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
    cout << "test " << endl;
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

void NotePad::addCompletion()
{
    schemaEditor->parseEditorForWordCompletion(xmlEditor);
    schemaEditor->parseEditorForWordCompletion(schemaEditor);
    xmlEditor->parseEditorForWordCompletion(schemaEditor);
    xmlEditor->parseEditorForWordCompletion(xmlEditor);
}

bool NotePad::isPathGreater(stack<int> s1, stack<int> s2) const
{
    if(s1.size() < s2.size())
    {
        return false;
    }
    if(s1.size() > s2.size())
    {
        return true;
    }
    while(true)
    {
        if(s1.top() > s2.top())
        {
            return true;
        }
        if(s1.top() < s2.top())
        {
            return false;
        }
        s1.pop();
        s2.pop();
    }
}

CustomTabWidget::CustomTabWidget() : QTabWidget::QTabWidget()
{
    dtdEnabled = false;
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Tab), this, SLOT(onTabHit()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_Tab), this, SLOT(onShiftTabHit()));
    new QShortcut(QKeySequence(Qt::Key_F4), this, SLOT(onToggle()));
    connect(this, SIGNAL(currentChanged(int)), this, SLOT(onTabChanged()));
}

void CustomTabWidget::disableSchema()
{
    dtdEnabled = false;
    setTabEnabled(1, false);
}

void CustomTabWidget::enableDTD()
{
    dtdEnabled = true;
    setTabEnabled(1, true);
}

bool CustomTabWidget::isDtdEnabled() const
{
    return dtdEnabled;
}

void CustomTabWidget::onTabHit()
{
    if(dtdEnabled)
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
        if(dtdEnabled)
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
    //enableDTD();
    XmlFileManager::getFileManager()->setActiveTab(currentIndex());
}
