#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    resize(800, 600);
    QHBoxLayout *layout = new QHBoxLayout;
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
    this->layout = layout;
    a->setLayout(this->layout);
    //this->setLayout(this->layout);
    this->setCentralWidget(a);
}

void MainWindow::setArbo(Arbo* arbo)
{
    this->arbo = arbo;
    this->layout->addWidget(this->arbo->getVue());

}

void MainWindow::setNotePad(NotePad *notepad)
{
    this->notepad = notepad;
    this->layout->addWidget(notepad->getTextEdit());

    indentAction = new QAction(tr("&Indent"), this);

    connect(indentAction, SIGNAL(triggered()), this, SLOT(onIndent()));

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(indentAction);
}

void MainWindow::onIndent()
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
