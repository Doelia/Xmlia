#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QMainWindow>
#include <QAction>
#include <QMenuBar>
#include <QShortcut>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QSplitter>

#include "arbo.h"
#include "modelexml.h"
#include "notepad.h"
#include "xmlfilemanager.h"
#include "iconbar.h"
#include "logger.h"

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
    void setIconBar(IconBar *iconbar);
    void setLogger(Logger *logger);

signals:
    void log(QString s, QColor c);

private slots:

    /*** Barre de menu **/
    void quit();
    void open();
    void openSchema();
    void genSchema();
    void deleteSchema();

    void save();
    void saveXmlAs();
    void saveSchemaAs();
    void indent();

public slots:

private:
    Arbo* arbo;
    NotePad *notepad;
    IconBar *iconbar;
    Logger *logger;

    QGridLayout* layout;
    QVBoxLayout *vLayout;
    QWidget *vContainer;
    QSplitter *hSplitter;

    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* schemaMenu;

    QAction* openAction;
    QAction* openSchemaAction;
    QAction* genSchemaAction;
    QAction* deleteSchemaAction;
    QAction* saveAction;
    QAction* exitAction;
    QAction* textChangedAction;
    QAction* indentAction;
};

#endif // MAINWINDOW_H
