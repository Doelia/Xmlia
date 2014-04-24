#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QTextEdit>
#include <QGridLayout>
#include <QWidget>
#include <QScrollBar>
#include <QTabWidget>
#include <QShortcut>
#include <texthighlighter.h>
#include <QEvent>
#include <QSourceLocation>
#include <QAbstractMessageHandler>

using namespace std;

class MessageHandler : public QAbstractMessageHandler
{
    Q_OBJECT
public:
    MessageHandler();
    void handleMessage(QtMsgType type, const QString &description, const QUrl &identifier, const QSourceLocation &sourceLocation);
signals:
    void log(QString, QColor);
    void error(int);
};

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
    void error(int);
    void cursorInfo(int, int);

protected:
    QTextEdit *text;
    QTextEdit *linesDisplay;
    QGridLayout *grid;
    QWidget *view;
    QSyntaxHighlighter *th;
    MessageHandler *mh;
    bool hasError;

public slots:
    void onScroll(int);
    void addLinesNumber();
    void resetLinesNumber();

protected slots:
    void onLog(QString, QColor);
    void onError(int);
};

#endif // TEXTEDITOR_H
