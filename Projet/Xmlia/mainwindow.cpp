#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    setFixedSize(1280, 800);
    QVBoxLayout *layout = new QVBoxLayout;
    this->setLayout(layout);

}
