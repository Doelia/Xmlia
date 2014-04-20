#ifndef LOGGER_H
#define LOGGER_H

#include <QWidget>
#include <QTextEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QIcon>

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

private:
    QTextEdit *logArea;
    QVBoxLayout *layout;
    QPushButton *toggleButton;

    QHBoxLayout *hLayout;
    QWidget *container;

    QIcon openIcon;
    QIcon closeIcon;

    void hide() const;
    void show() const;

};

#endif // LOGGER_H
