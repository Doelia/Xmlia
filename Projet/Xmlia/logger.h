#ifndef LOGGER_H
#define LOGGER_H

/*===============================================
 * nom : logger.h         projet : xmlia
 * widget du logger
 *=============================================*/

#include <QWidget>
#include <QTextEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QIcon>
#include <QScrollBar>
#include <QDateTime>

class Logger : public QWidget
{
    Q_OBJECT
public:
    explicit Logger();

    QWidget *getView() const;
    
signals:
    
public slots:
    /**
     * @brief log affiche s avec la couleur c dans la zone de texte
     * @param s
     * @param c
     */
    void log(QString s, QColor c);

    /**
     * @brief toggle masque ou affiche la zone d'affichage
     */
    void toggle() const;

    /**
     * @brief setCursorInfo affiche la position du curseur dans le document
     */
    void setCursorInfo(int, int);

private slots:
    /**
     * @brief disableScroll empeche le scrolling de la zone de texte des lignes/colonnes
     */
    void disableScroll();

private:
    QTextEdit *logArea;
    QTextEdit *cursorInfo;
    QVBoxLayout *layout;
    QPushButton *toggleButton;


    QHBoxLayout *hLayout;
    QWidget *container;

    QIcon openIcon;
    QIcon closeIcon;

    /**
     * @brief hide masque la zone de texte
     */
    void hide() const;

    /**
     * @brief show affiche la zone de texte
     */
    void show() const;

    int fixedScroll;
};

#endif // LOGGER_H
