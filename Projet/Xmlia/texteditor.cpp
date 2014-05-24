/*===============================================
 * nom : texteditor.cpp         projet : xmlia
 *=============================================*/

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

    antiRecursion = false;

    setFocusPolicy(Qt::StrongFocus);

    connect(mh, SIGNAL(error(int)), this, SLOT(onError(int)));
    connect(mh, SIGNAL(log(QString,QColor)), this, SLOT(onLog(QString,QColor)));
    connect(linesDisplay->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(onScroll(int)));
    connect(text->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(onScroll(int)));
    connect(text, SIGNAL(textChanged()), this, SLOT(addLinesNumber()));
    connect(text, SIGNAL(textChanged()), this, SLOT(popupCompletion()));
    connect(this, SIGNAL(error(int)), this, SLOT(onError(int)));

    word.setPattern("[a-zA-Z]+");
}

void TextEditor::indent()
{
    int selectionStart = text->textCursor().selectionStart();
    int selectionEnd = text->textCursor().selectionEnd();

    tabNumber = 0;

    QTextCursor c = text->textCursor();

    c.setPosition(selectionStart);
    int upperBound = c.blockNumber();
    c.movePosition(QTextCursor::StartOfBlock);
    selectionStart = c.selectionStart();

    c.setPosition(selectionEnd);
    int lowerBound = c.blockNumber();
    c.movePosition(QTextCursor::StartOfBlock);
    selectionEnd = c.selectionEnd();

    QString s = text->toPlainText();
    QStringList line = s.split("\n");

    QXmlStreamReader xml(this->text->toPlainText());

    int last = 0;

    while(!xml.atEnd())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        for (int var = last; var < xml.lineNumber(); ++var)
        {
            indentLineWithBounds(&line, var, upperBound, lowerBound);
        }

        if(token == QXmlStreamReader::StartElement)
        {
            if(last != xml.lineNumber())
            {
                last = xml.lineNumber();
                indentLineWithBounds(&line, last - 1, upperBound, lowerBound);
            }
            tabNumber++;
        }
        else if(token == QXmlStreamReader::EndElement)
        {
            tabNumber--;
            last = xml.lineNumber();
            indentLineWithBounds(&line, last - 1, upperBound, lowerBound);
        }
    }

    if(selectionStart < s.length() - 1)
    {
        text->setPlainText(line.join("\n"));
    }
    c.setPosition(selectionEnd);
    c.movePosition(QTextCursor::EndOfLine);
    text->setTextCursor(c);
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

void TextEditor::parseEditorForWordCompletion(TextEditor *t)
{
    QRegExp rx(":|/|<|>| |=|\"");
    QStringList l = t->text->toPlainText().split(rx, QString::SkipEmptyParts);
    for(QString s : l)
    {
        if(word.indexIn(s) >= 0)
        {
            cout << s.toStdString() << endl;
            if(!wordsForCompletion.contains(s))
            {
                wordsForCompletion << s;
            }
        }
    }
    delete completer;
    completer = new QCompleter(wordsForCompletion);
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

void TextEditor::popupCompletion()
{
    if(!antiRecursion)
    {
        completer->setCompletionPrefix(textUnderCursor());
        QString completion = completer->currentCompletion();
        QString currentWord = textUnderCursor();

        if(currentWord.size() > 0 && currentWord.size() < completion.size())
        {
            QTextCursor cursor = text->textCursor();
            int pos = cursor.position();

            while(word.indexIn(cursor.selectedText()) == 0)
            {
                cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor);
            }

            cursor.insertText(completion.right(completion.size() - currentWord.size()));
            cursor.setPosition(pos, QTextCursor::KeepAnchor);
            text->setTextCursor(cursor);
        }
    }
    antiRecursion = !antiRecursion;
}

void TextEditor::indentLineWithBounds(QStringList *list, int line, int upperBound, int lowerBound)
{
    if(line >= upperBound && line <= lowerBound)
    {
        QRegExp regex("^(\\s)*");
        QString content = list->at(line).split(regex)[1];

        QString res;
        res.append(tabsString(tabNumber)).append(content);

        list->removeAt(line);
        list->insert(line, res);
    }
}

QString TextEditor::tabsString(int n) const
{
    QString l;
    for (int i = 0; i < n; i++) {
        for (int var = 0; var < NB_SPACE; ++var) {
            l.append(" ");
        }
    }
    return l;
}

QString TextEditor::textUnderCursor() const
{
    QTextCursor c = text->textCursor();
    c.movePosition(QTextCursor::Left);
    c.select(QTextCursor::WordUnderCursor);
    QString s = c.selectedText();
    cout << "under cursor : " << s.toStdString() << endl;
    return c.selectedText();
}

bool TextEditor::insertCompletion()
{
    QTextCursor cursor = text->textCursor();
    int pos = cursor.position();
    cursor.movePosition(QTextCursor::EndOfWord);
    if(pos != cursor.position())
    {
        text->setTextCursor(cursor);
        return true;
    }
    return false;
}

void TextEditor::removeCompletion()
{
    if(completer->currentCompletion().size() > 0)
    {
        QTextCursor cursor = text->textCursor();
        antiRecursion = true;
        cursor.removeSelectedText();
        text->setTextCursor(cursor);
        antiRecursion = true;
    }
}

MessageHandler::MessageHandler(){}

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
