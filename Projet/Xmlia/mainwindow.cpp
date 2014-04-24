#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    resize(800, 600);
    //
    openAction = new QAction(tr("&Open"), this);
    saveAction = new QAction(tr("&Save"), this);
    exitAction = new QAction(tr("E&xit"), this);

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    QWidget *widgetContainer = new QWidget();
    this->layout = new QGridLayout();
    widgetContainer->setLayout(this->layout);
    this->setCentralWidget(widgetContainer);

    this->hSplitter = new QSplitter(Qt::Horizontal);

    this->vLayout = new QVBoxLayout();
    this->vLayout->setMargin(0);
    this->vLayout->setSpacing(5);
    this->vContainer = new QWidget();

    this->layout->setMargin(5);
    this->layout->activate();

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_O), this, SLOT(open()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this, SLOT(save()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_S), this, SLOT(saveAs()));
}

void MainWindow::setArbo(Arbo* arbo)
{
    this->arbo = arbo;
    cout << "MainWindow::SetArbo() : Récuperation de la vue..." << endl;
    QTreeView* temp = this->arbo->getVue();
    cout << "MainWindow::SetArbo() : Vue récuperée" << endl;
    this->layout->setSpacing(0);

    hSplitter->addWidget(temp);
    QList<int> sizes;
    sizes.append(this->width() / 7);
    hSplitter->setSizes(sizes);

    cout << "MainWindow::SetArbo(): Vue ajoutée au layout" << endl;

    connect(XmlFileManager::getFileManager()->getModele(), SIGNAL(onNodeDelete(QDomNode)), this->arbo, SLOT(onNodeDelete(QDomNode)));

}

void MainWindow::setNotePad(NotePad *notepad)
{
    this->notepad = notepad;
    vLayout->addWidget(notepad->getView(), 4);

    indentAction = new QAction(tr("&Indent"), this);

    connect(indentAction, SIGNAL(triggered()), this, SLOT(indent()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_I), this, SLOT(indent()));

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(indentAction);

    QShortcut *refresh = new QShortcut(this);
    refresh->setKey(QKeySequence(Qt::CTRL + Qt::Key_R));

    // Signaux
    connect(this->notepad, SIGNAL(update()), arbo, SLOT(updateView())); // Provisoire
    connect(XmlFileManager::getFileManager()->getModele(), SIGNAL(onNodeNameUpdate(QDomNode, QString)), this->notepad, SLOT(onNodeNameUpdate(QDomNode, QString)));
    connect(XmlFileManager::getFileManager()->getModele(), SIGNAL(onNodeDelete(QDomNode)), this->notepad, SLOT(onNodeDelete(QDomNode)));
     connect(XmlFileManager::getFileManager()->getModele(), SIGNAL(onNodeInsert(QDomNode, QDomNode)), this->notepad, SLOT(onNodeInsert(QDomNode, QDomNode)));
    connect(refresh, SIGNAL(activated()), this->notepad, SLOT(onRefreshRequest()));
}

void MainWindow::setIconBar(IconBar *iconbar)
{
    this->iconbar = iconbar;
    this->layout->addWidget(iconbar, 0, 0);
    this->layout->addWidget(hSplitter, 1, 0);
    this->iconbar->setFixedHeight(40);

    this->iconbar->connectOpen(this);
    this->iconbar->connectSave(this);
    this->iconbar->connectSaveAs(this);
    this->iconbar->connectIndent(this);
    this->iconbar->connectBuild(this->notepad);
}

void MainWindow::setLogger(Logger *logger)
{
    this->logger = logger;
    vLayout->addWidget(logger);
    vContainer->setLayout(vLayout);
    layout->setHorizontalSpacing(5);

    //layout->addWidget(vContainer, 1, 2, 2, 6);

    hSplitter->addWidget(vContainer);

    QShortcut *toggleLogger = new QShortcut(this);
    toggleLogger->setKey(QKeySequence(Qt::CTRL + Qt::Key_L));

    connect(toggleLogger, SIGNAL(activated()), this->logger, SLOT(toggle()));
    connect(notepad, SIGNAL(log(QString,QColor)), this->logger, SLOT(log(QString,QColor)));
    connect(this, SIGNAL(log(QString,QColor)), this->logger, SLOT(log(QString,QColor)));
    connect(XmlFileManager::getFileManager(), SIGNAL(log(QString,QColor)), this->logger, SLOT(log(QString,QColor)));
    connect(notepad, SIGNAL(cursorInfo(int,int)), this->logger, SLOT(setCursorInfo(int,int)));
}

void MainWindow::indent()
{
    this->notepad->indent();
}

void MainWindow::quit()
{
    qApp->quit();
}

void MainWindow::open()
{
    QString currentFile = QFileDialog::getOpenFileName(this, tr("Open File"), "",
                                                       tr("Xml Files (*.x*);;All Files (*.*)"));

    if(currentFile != "")
    {
        XmlFileManager::getFileManager()->setCurrentFile(currentFile);
        XmlFileManager::getFileManager()->openFile(notepad);

        //this->notepad->setText(XmlFileManager::getFileManager()->getModele()->domToString());
        this->arbo->updateView();
    }

}
void MainWindow::save()
{
    if(XmlFileManager::getFileManager()->getCurrentFile() != "")
    {
        XmlFileManager::getFileManager()->saveFile(notepad);
    }
    else
    {
        saveAs();
    }
}

void MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "",
                                                    tr("Xml Files (*.xml)"));

    if (fileName != "") {
        XmlFileManager::getFileManager()->setCurrentFile(fileName);
        save();
    }
}
