#include "texthighlighter.h"

using namespace std;

#define DEFAULT_STATE -1
#define QUOTE_STATE 0
#define TAG_STATE 1

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
        if (text.mid(i, 1) == "\"")
        {
            if (currentBlockState() == QUOTE_STATE)
            {
                setCurrentBlockState(DEFAULT_STATE);
                setFormat(last, i - last + 1, Qt::blue);
            }
            else
            {
                setCurrentBlockState(QUOTE_STATE);
                last = i;
            }
        }

        else if (text.mid(i, 1) == "<")
        {
            last = i + ((text.mid(i + 1, 1) == "/")?2:1);
            setCurrentBlockState(TAG_STATE);

        }

        else if (currentBlockState() == TAG_STATE && text.mid(i, 1) == ">")
        {
            setFormat(last, i - last, Qt::red);
            setCurrentBlockState(DEFAULT_STATE);
        }
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
