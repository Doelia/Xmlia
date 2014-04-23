#ifndef TEXTHIGHLIGHTER_H
#define TEXTHIGHLIGHTER_H

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
    
    void incrementTabNumber();
    void decrementTabNumber();
    int getTabNumber() const;
    void clearTabNumber();

    void setDocument(QTextDocument *doc);

    void setTextColor(int last, int current, QColor c);

    bool cComment(int *last, const QString &text, int i);
    bool cQuote(int *last, const QString &text, int i);
    bool cTag(int *last, const QString &text, int i);
    bool cInTagAttr(int *last, const QString &text, int i);

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
