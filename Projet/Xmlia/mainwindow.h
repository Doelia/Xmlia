#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QVBoxLayout>

#include "arbo.h"

/**
  Fenetre principale du programme
  Contient les différentes vues
**/

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    void setArbo(Arbo* arbo);
    
signals:
    
public slots:

private:
    Arbo* arbo;
    QVBoxLayout* layout;
    
};

#endif // MAINWINDOW_H
