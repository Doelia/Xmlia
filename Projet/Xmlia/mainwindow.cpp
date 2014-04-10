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


    QWidget *a = new QWidget();
    this->layout = new QHBoxLayout();
    a->setLayout(this->layout);
    this->setCentralWidget(a);


    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_O), this, SLOT(open()));
}

void MainWindow::setArbo(Arbo* arbo)
{
    this->arbo = arbo;
    cout << "recuperation de la vue" << endl;
    QTreeView* temp = this->arbo->getVue();
    cout << "vue recuperee" << endl;
    cout << "ajout au layout" << endl;
    this->layout->addWidget(temp);
    cout << "ajoute au layout" << endl;
}

void MainWindow::setNotePad(NotePad *notepad)
{
    this->notepad = notepad;
    this->layout->addWidget(notepad->getTextEdit());

    indentAction = new QAction(tr("&Indent"), this);

    connect(indentAction, SIGNAL(triggered()), this, SLOT(indent()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_I), this, SLOT(indent()));

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(indentAction);

    connect(this->notepad, SIGNAL(update()), arbo, SLOT(updateView()));
    connect(XmlFileManager::getFileManager()->getModele(), SIGNAL(onNodeNameUpdate(QDomNode, QString)), this->notepad, SLOT(onNodeNameUpdate(QDomNode, QString)));
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
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
                                                    tr("Xml Files (*.xml);;Text Files (*.txt)"));

    cout << fileName.toStdString() << endl;

    XmlFileManager::getFileManager()->openFile(fileName);

    this->notepad->setText(XmlFileManager::getFileManager()->getModele()->domToString());
    this->arbo->updateView();
}

void MainWindow::save()
{
   /*QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "",
                                                    tr("Text Files (*.txt);;Xml Files (*.xml)"));

    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            // error message
        } else {
            QTextStream stream(&file);
            stream << notepad->text->toPlainText();
            stream.flush();
            file.close();
        }
    }*/
}
