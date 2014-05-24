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
#include <QRegExp>

using namespace std;

class MessageHandler : public QAbstractMessageHandler
{
    Q_OBJECT
public:
    MessageHandler();
    void handleMessage(QtMsgType type, const QString &description, const QUrl &identifier, const QSourceLocation &sourceLocation);
signals:
    /**
     * @brief log signal du MessageHandler pour la validation sémantique
     */
    void log(QString, QColor);
    /**
     * @brief error affiche l'erreur dans le logger pour la validation sémantique
     */
    void error(int);
};

class TextEditor : public QWidget
{
    Q_OBJECT
public:
    TextEditor(QSyntaxHighlighter *s);
    /**
     * @brief indent indente le texte
     */
    void indent();

    /**
     * @brief setText set le texte du document de s
     * @param s
     */
    void setText(QString s);

    /**
     * @brief getText
     * @return le texte du document
     */
    QString getText() const;

    /**
     * @brief getView
     * @return le widget de vue pour l'affichage
     */
    QWidget* getView() const;

    /**
     * @brief parseStringForCompletion adds each word of the string to the word completion list
     * @param s
     */
    void parseEditorForWordCompletion(TextEditor* t);

signals:
    /**
     * @brief log demande de log s de la couleur c
     * @param s
     * @param c
     */
    void log(QString s, QColor c);

    /**
     * @brief error envoi la ligne de l'erreur
     */
    void error(int);

    /**
     * @brief cursorInfo demande d'afficher la position du curseur
     */
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
    QRegExp word;
    QStringList wordsForCompletion;

    /**
     * @brief textUnderCursor
     * @return le mot sous le curseur pour l'autocompletion
     */
    QString textUnderCursor() const;

    /**
     * @brief insertCompletion
     * @return true si la completion a ete inseree
     */
    bool insertCompletion();

    /**
     * @brief removeCompletion efface la completion courante
     */
    void removeCompletion();

    /**
     * @brief indentLineWithBounds indent le texte entre upperBound et lowerBound
     * @param list
     * @param line
     * @param upperBound
     * @param lowerBound
     */
    void indentLineWithBounds(QStringList *list, int line, int upperBound, int lowerBound);

    /**
      @return la ligne indentée de n tab
      */
    QString tabsString(int n) const;


public slots:
    void onScroll(int);
    /**
     * @brief addLinesNumber affiche le numero des lignes
     */
    void addLinesNumber();
    /**
     * @brief resetLinesNumber clear le numero des lignes
     */
    void resetLinesNumber();

protected slots:
    void onLog(QString, QColor);
    void onError(int);
    /**
     * @brief popupCompletion affiche l'autocompletion
     */
    void popupCompletion();
};

#endif // TEXTEDITOR_H
