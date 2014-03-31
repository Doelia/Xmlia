#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    setFixedSize(800, 600);
    QVBoxLayout *layout = new QVBoxLayout;
    this->setLayout(layout);
    this->layout = layout;
    //
}

void MainWindow::setArbo(Arbo* arbo)
{
    this->arbo = arbo;
    this->layout->addWidget(this->arbo->getVue());

}
