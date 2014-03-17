#ifndef TEXTHIGHLIGHTER_H
#define TEXTHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <iostream>
#include <QTextEdit>

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
    void setTextColor(int last, int current, QColor c);

    bool cComment(int *last, const QString &text, int i);
    bool cQuote(int *last, const QString &text, int i);
    bool cTag(int *last, const QString &text, int i);
    bool cInTagAttr(int *last, const QString &text, int i);

signals:
    
public slots:

private:
    int tabNumber;

};

#endif // TEXTHIGHLIGHTER_H
