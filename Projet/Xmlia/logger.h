#ifndef LOGGER_H
#define LOGGER_H

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
    void log(QString s, QColor c);
    void toggle() const;
    void setCursorInfo(int, int);

private slots:
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

    void hide() const;
    void show() const;

    int fixedScroll;
};

#endif // LOGGER_H
