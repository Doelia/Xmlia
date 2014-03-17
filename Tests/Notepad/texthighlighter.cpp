#include "texthighlighter.h"

using namespace std;

#define DEFAULT_STATE -1
#define QUOTE_STATE 0
#define TAG_STATE 1
#define COMMENT_STATE 2
#define IN_TAG_ATTR_STATE 3

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
        if(currentBlockState() == COMMENT_STATE)
        {
            last = i;
            if (text.mid(i, 3) == "-->")
            {
                setCurrentBlockState(DEFAULT_STATE);
            }
        }
        else
        {
            if (text.mid(i, 1) == "\"")
            {
                if (currentBlockState() == QUOTE_STATE)
                {
                    setCurrentBlockState(DEFAULT_STATE);
                }
                else
                {
                    setCurrentBlockState(QUOTE_STATE);
                    last = i + 1;
                }
            }

            else if (currentBlockState() == TAG_STATE && text.mid(i, 1) == " ")
            {
                last = i;
                setCurrentBlockState(IN_TAG_ATTR_STATE);
            }

            else if (text.mid(i, 4) == "<!--")
            {
                last = i;
                setCurrentBlockState(COMMENT_STATE);
            }

            else if (text.mid(i, 1) == "<")
            {
                last = i + ((text.mid(i + 1, 1) == "/")?2:1);
                setCurrentBlockState(TAG_STATE);
            }

            else if (currentBlockState() == TAG_STATE && text.mid(i, 1) == ">")
            {
                setCurrentBlockState(DEFAULT_STATE);
            }
        }
        setTextColor(last, i);

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

void TextHighLighter::setTextColor(int last, int current)
{
    switch(currentBlockState())
    {
    case (DEFAULT_STATE): {break;}
    case(TAG_STATE): {setFormat(last, current - last + 1, Qt::red);break;}
    case(QUOTE_STATE): {setFormat(last, current - last + 1, Qt::blue);break;}
    case(COMMENT_STATE): {setFormat(last, current - last + 4, Qt::gray);break;}
    case(IN_TAG_ATTR_STATE): {setFormat(last, current - last + 1, Qt::cyan);break;}
    }
}
