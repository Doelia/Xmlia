#include "texteditor.h"

TextEditor::TextEditor(QSyntaxHighlighter *s)
{
    std::cout << "TextEditor::TextEditor" << std::endl;
    this->linesDisplay = new QTextEdit();
    this->text = new QTextEdit();
    s->setDocument(text->document());

    this->grid = new QGridLayout();
    this->grid->setMargin(0);
    this->grid->setSpacing(1);

    linesDisplay->setReadOnly(true);
    linesDisplay->setWordWrapMode(QTextOption::NoWrap);
    linesDisplay->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    linesDisplay->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    linesDisplay->setTextColor(Qt::darkGray);
    linesDisplay->setText("1");
    linesDisplay->setStyleSheet("* { background-color: rgb(200, 200, 200); border-color: gray; border-style: outset; border-width: 2px;}");
    linesDisplay->setFixedWidth(38);

    text->setStyleSheet("* { border-color: gray; border-style: outset; border-width: 2px;}");
    text->setWordWrapMode(QTextOption::NoWrap);

    grid->addWidget(linesDisplay, 0, 0);
    grid->addWidget(text, 0, 1);

    this->view = new QWidget();
    this->view->setLayout(grid);

    this->th = s;
    this->th->rehighlight();

    connect(linesDisplay->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(onScroll(int)));
    connect(text->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(onScroll(int)));
    connect(text, SIGNAL(textChanged()), this, SLOT(addLinesNumber()));
}

void TextEditor::setText(QString s)
{
    text->setText(s);
}

QString TextEditor::getText() const
{
    return text->toPlainText();
}

QWidget *TextEditor::getView() const
{
    return this->view;
}

void TextEditor::onScroll(int y)
{
    linesDisplay->verticalScrollBar()->setValue(text->verticalScrollBar()->value());
}

void TextEditor::addLinesNumber()
{
    while(linesDisplay->document()->blockCount() < text->document()->blockCount())
    {
        linesDisplay->setAlignment(Qt::AlignRight);
        linesDisplay->append(QString::number(linesDisplay->document()->blockCount() + 1));
    }
}

void TextEditor::resetLinesNumber()
{
    int n = linesDisplay->document()->blockCount();
    linesDisplay->setText("1");
    for (int i = 0; i < n - 1; ++i) {
        linesDisplay->setAlignment(Qt::AlignRight);
        linesDisplay->append(QString::number(linesDisplay->document()->blockCount() + 1));
    }
}
