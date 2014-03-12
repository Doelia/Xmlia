#ifndef TEXTHIGHLIGHTER_H
#define TEXTHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <iostream>
#include <QTextEdit>

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
    void setTextColor(int last, int current);

signals:
    
public slots:

private:
    int tabNumber;

};

#endif // TEXTHIGHLIGHTER_H
