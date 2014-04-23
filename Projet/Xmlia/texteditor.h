#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QTextEdit>
#include <QGridLayout>
#include <QWidget>
#include <QScrollBar>
#include <QTabWidget>
#include <QShortcut>
#include <texthighlighter.h>

class TextEditor : public QWidget
{
    Q_OBJECT
public:
    TextEditor(QSyntaxHighlighter *s);

    void setText(QString s);
    QString getText() const;
    QWidget* getView() const;

signals:
    void log(QString s, QColor c);

protected:
    QTextEdit *text;
    QTextEdit *linesDisplay;
    QGridLayout *grid;
    QWidget *view;
    QSyntaxHighlighter *th;
public slots:
    void onScroll(int);
    void addLinesNumber();
    void resetLinesNumber();

};

#endif // TEXTEDITOR_H
