#include "texthighlighter.h"

using namespace std;

TextHighLighter::TextHighLighter(QTextDocument *parent) :
    QSyntaxHighlighter(parent)
{
    this->tabNumber = 0;
}

void TextHighLighter::highlightBlock(const QString &text)
{
    int last = 0;

    setCurrentBlockState(previousBlockState());

    for (int i = 0; i < text.length(); ++i)
    {
        if(cComment(&last, text, i));
        else if(cQuote(&last, text, i));
        else if(cInTagAttr(&last, text, i));
        else if(cTag(&last, text, i));
    }
}

void TextHighLighter::incrementTabNumber()
{
    tabNumber++;
}

void TextHighLighter::decrementTabNumber()
{
    if(tabNumber > 0)
    {
        tabNumber--;
    }
}

int TextHighLighter::getTabNumber() const
{
    return tabNumber;
}

void TextHighLighter::clearTabNumber()
{
    tabNumber = 0;
}

void TextHighLighter::setTextColor(int last, int current, QColor c)
{
    setFormat(last, current - last, c);
}

bool TextHighLighter::cComment(int *last, const QString &text, int i)
{
    if(currentBlockState() == COMMENT_STATE)
    {
        if (text.mid(i, 3) == "-->")
        {
            setTextColor(*last, i + 4, Qt::gray);
            setCurrentBlockState(DEFAULT_STATE);
        }
        setTextColor(*last, i + 1, Qt::gray);
        return true;
    }
    else if (text.mid(i, 4) == "<!--")
    {
        *last = i;
        setCurrentBlockState(COMMENT_STATE);
        return true;
    }
    return false;
}

bool TextHighLighter::cQuote(int *last, const QString &text, int i)
{
    bool equalsQuote = (text.mid(i, 1) == "\"");

    if(currentBlockState() == QUOTE_STATE)
    {
        if (equalsQuote)
        {
            setCurrentBlockState(DEFAULT_STATE);
            setTextColor(*last, i, Qt::blue);
            return true;
        }
        setTextColor(*last, i + 1, Qt::blue);
        return true;
    }
    else if (equalsQuote)
    {
        setCurrentBlockState(QUOTE_STATE);
        *last = i + 1;
        setTextColor(*last, i, Qt::blue);
        return true;
    }
    return false;
}

bool TextHighLighter::cTag(int *last, const QString &text, int i)
{
    if(currentBlockState() == TAG_STATE)
    {
        if(text.mid(i, 1) == ">")
        {
            setCurrentBlockState(DEFAULT_STATE);
            setTextColor(*last, i, Qt::red);
            return true;
        }
        setTextColor(*last, i + 1, Qt::red);
        return true;
    }
    else if (text.mid(i, 1) == "<")
    {
        *last = i + ((text.mid(i + 1, 1) == "/")?2:1);
        setCurrentBlockState(TAG_STATE);
        setTextColor(*last, i + 1, Qt::red);
        return true;
    }
    return false;
}

bool TextHighLighter::cInTagAttr(int *last, const QString &text, int i)
{
    if(currentBlockState() == IN_TAG_ATTR_STATE)
    {
        setTextColor(*last, i + 1, Qt::cyan);
        return true;
    }
    else if (currentBlockState() == TAG_STATE && text.mid(i, 1) == " ")
    {
        *last = i;
        setCurrentBlockState(IN_TAG_ATTR_STATE);
        return true;
    }
    return false;
}
