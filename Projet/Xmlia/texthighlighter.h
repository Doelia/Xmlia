#ifndef TEXTHIGHLIGHTER_H
#define TEXTHIGHLIGHTER_H

/*===============================================
 * nom : texthighlighter.h         projet : xmlia
 * colorateur syntaxique
 *=============================================*/

#include <QSyntaxHighlighter>
#include <iostream>
#include <QTextEdit>
#include <QColor>

#define DEFAULT_STATE -1
#define QUOTE_STATE 0
#define TAG_STATE 1
#define COMMENT_STATE 2
#define IN_TAG_ATTR_STATE 3

class TextHighLighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    TextHighLighter(QTextDocument* doc);
    void highlightBlock(const QString &text);

    void setDocument(QTextDocument *doc);

    void setTextColor(int last, int current, QColor c);

    /**
     * @brief cComment
     * @param last
     * @param text
     * @param i
     * @return true si un commentaire a ete colore
     */
    bool cComment(int &last, const QString &text, int i);

    /**
     * @brief cQuote
     * @param last
     * @param text
     * @param i
     * @return true si un texte entre quote a ete colore
     */
    bool cQuote(int &last, const QString &text, int i);

    /**
     * @brief cTag
     * @param last
     * @param text
     * @param i
     * @return true si une balise a ete coloree
     */
    bool cMarkup(int &last, const QString &text, int i);

    /**
     * @brief cInTagAttr
     * @param last
     * @param text
     * @param i
     * @return true si un attribut a ete colore
     */
    bool cInMarkupAttr(int &last, const QString &text, int i);

signals:
    
public slots:

private:
    int tabNumber;
    bool isTagOpen;

    QColor *tag = new QColor(18, 59, 171);
    QColor *inTagAttr = new QColor(0, 176, 100);
    QColor *quote = new QColor(255, 159, 0);

};

#endif // TEXTHIGHLIGHTER_H
