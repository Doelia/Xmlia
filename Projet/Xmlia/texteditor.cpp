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
    linesDisplay->setAlignment(Qt::AlignRight);
    linesDisplay->append("1");
    linesDisplay->setStyleSheet("* { background-color: rgb(200, 200, 200); border-color: gray; border-style: outset; border-width: 2px;}");
    linesDisplay->setFixedWidth(38);

    text->setStyleSheet("* { border-color: gray; border-style: outset; border-width: 2px;}");
    text->setWordWrapMode(QTextOption::NoWrap);
    text->setAcceptRichText(false);

    grid->addWidget(linesDisplay, 0, 0);
    grid->addWidget(text, 0, 1);

    this->view = new QWidget();
    this->view->setLayout(grid);

    this->th = s;
    this->th->rehighlight();

    mh = new MessageHandler();

    connect(mh, SIGNAL(error(int)), this, SLOT(onError(int)));
    connect(mh, SIGNAL(log(QString,QColor)), this, SLOT(onLog(QString,QColor)));
    connect(linesDisplay->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(onScroll(int)));
    connect(text->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(onScroll(int)));
    connect(text, SIGNAL(textChanged()), this, SLOT(addLinesNumber()));
    connect(this, SIGNAL(error(int)), this, SLOT(onError(int)));
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
    if(text->document()->blockCount() < 50 && text->document()->blockCount() < linesDisplay->document()->blockCount())
    {
        linesDisplay->document()->clear();
        linesDisplay->setTextColor(Qt::darkGray);
        linesDisplay->setAlignment(Qt::AlignRight);
        linesDisplay->append("1");
    }
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

void TextEditor::onLog(QString s, QColor c)
{
    emit log(s, c);
}

void TextEditor::onError(int line)
{
    QTextCursor c = linesDisplay->textCursor();
    c.setPosition(0);
    c.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, line);
    QTextBlockFormat b;
    b.setBackground(QColor("red"));
    c.setBlockFormat(b);
    linesDisplay->setTextCursor(c);

    c = text->textCursor();
    c.setPosition(0);
    c.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, line);
    text->setTextCursor(c);
    text->ensureCursorVisible();
}


MessageHandler::MessageHandler()
{
}

void MessageHandler::handleMessage(QtMsgType type, const QString &description, const QUrl &identifier, const QSourceLocation &sourceLocation)
{
    QString s(description);
    s.remove(QRegExp("<html xmlns.*<p>"));
    s.replace(QRegExp("<span class='XQuery-keyword'>"), "\"");
    s.replace(QRegExp("<span class='XQuery-data'>"), "\"");
    s.replace(QRegExp("<span class='XQuery-type'>"), "\"");
    s.replace("</span>", "\"");
    s.remove("</p></body></html>");
    emit log(QString("Erreur ligne ").append(QString::number(sourceLocation.line())).append(" colonne ").append(QString::number(sourceLocation.column())).append("\n").append(s), QColor("red"));
    emit error(sourceLocation.line() - 1);
}
