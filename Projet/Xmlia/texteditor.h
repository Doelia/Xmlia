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
#include <QXmlStreamReader>
#include <QAbstractMessageHandler>
#include <QCompleter>
#include <QTextCursor>
#include <QKeyEvent>
#include <QAbstractItemView>
#include <QRect>
#include <QCompleter>

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
    void indent();
    void setText(QString s);
    QString getText() const;
    QWidget* getView() const;

signals:
    void log(QString s, QColor c);
    void error(int);
    void cursorInfo(int, int);

 private slots:

protected:
    int NB_SPACE = 8;
    QTextEdit *text;
    QTextEdit *linesDisplay;
    QGridLayout *grid;
    QWidget *view;
    QSyntaxHighlighter *th;
    MessageHandler *mh;
    bool hasError;
    int tabNumber;
    QCompleter *completer;
    bool antiRecursion;

    QString textUnderCursor() const;
    bool insertCompletion();
    void removeCompletion();

    /**
      indente le texte sélectionné par l'utilisateur (entre upperBound et lowerBound)
      */
    void indentLineWithBounds(QStringList *list, int line, int upperBound, int lowerBound);

    /**
      @return la ligne indentée de n tab
      */
    QString tabsString(int n) const;

public slots:
    void onScroll(int);
    void addLinesNumber();
    void resetLinesNumber();

protected slots:
    void onLog(QString, QColor);
    void onError(int);
    void popupCompletion();
};

#endif // TEXTEDITOR_H
