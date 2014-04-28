#ifndef ICONBAR_H
#define ICONBAR_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>

class IconBar : public QWidget
{
    Q_OBJECT
public:
    explicit IconBar(QWidget *parent = 0);

    /*
     * connecte les boutons à l'action correspondante
     */
    void connectOpen(QObject*);
    void connectSave(QObject*);
    void connectSaveAs(QObject*);
    void connectIndent(QObject*);
    void connectBuild(QObject*, QObject*);
    
signals:
    
public slots:

private:
    QPushButton *open;
    QPushButton *save;
    QPushButton *saveAs;
    QPushButton *indent;
    QPushButton *build;

    QHBoxLayout *layout;

    /**
     * @brief createButton cree un bouton avec pour image path
     * @param path
     * @return
     */
    QPushButton *createButton(QString path) const;
};

#endif // ICONBAR_H
