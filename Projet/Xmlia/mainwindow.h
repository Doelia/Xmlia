#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QHBoxLayout>

#include "arbo.h"
#include "notepad.h"
#include "xmlfilemanager.h"
/**
  Fenetre principale du programme
  Contient les différentes vues
**/

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    void setArbo(Arbo* arbo);
    void setNotePad(NotePad *notepad);
    
signals:

private slots:
    void quit();
    void open();
    void save();
    void onIndent();

public slots:

private:
    Arbo* arbo;
    QHBoxLayout* layout;
    NotePad *notepad;

    QMenu* fileMenu;
    QMenu* editMenu;

    QAction* openAction;
    QAction* saveAction;
    QAction* exitAction;
    QAction* textChangedAction;
    QAction* indentAction;
    
};

#endif // MAINWINDOW_H
