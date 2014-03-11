#include "notepad.h"

NotePad::NotePad()
{
    this->text = new QTextEdit();
    this->th = new TextHighLighter(text->document());
    this->reader = new QXmlStreamReader();
    this->pile = new stack<QString>();

    this->text->installEventFilter(this);

    openAction = new QAction(tr("&Open"), this);
    saveAction = new QAction(tr("&Save"), this);
    exitAction = new QAction(tr("E&xit"), this);
    toRedAction = new QAction(tr("&Red"), this);
    toGreenAction = new QAction(tr("&Green"), this);
    toBlackAction = new QAction(tr("&Black"), this);
    indentAction = new QAction(tr("&Indent"), this);

    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(toRedAction, SIGNAL(triggered()), this, SLOT(toRed()));
    connect(toGreenAction, SIGNAL(triggered()), this, SLOT(toGreen()));
    connect(toBlackAction, SIGNAL(triggered()), this, SLOT(toBlack()));
    connect(text, SIGNAL(textChanged()), this, SLOT(onTextChange()));
    connect(indentAction, SIGNAL(triggered()), this, SLOT(onIndent()));

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    changeColorMenu = editMenu->addMenu("&Change color");
    changeColorMenu->addAction(toRedAction);
    changeColorMenu->addAction(toGreenAction);
    changeColorMenu->addAction(toBlackAction);
    editMenu->addAction(indentAction);

    setCentralWidget(text);

    setWindowTitle("superman");

    //this->xml = new QDomDocument();
}

void NotePad::quit()
{
    qApp->quit();
}

void NotePad::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
                                                    tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        QTextStream in(&file);
        text->setText(in.readAll());
        file.close();
    }
}

void NotePad::save()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "",
                                                    tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            // error message
        } else {
            QTextStream stream(&file);
            stream << text->toPlainText();
            stream.flush();
            file.close();
        }
    }
}

void NotePad::toBlack()
{
    text->setTextColor(QColor("black"));
}

void NotePad::toGreen()
{
    text->setTextColor(QColor("green"));
}

void NotePad::toRed()
{
    text->setTextColor(QColor("red"));
}

void NotePad::parse()
{
}

void NotePad::onTextChange()
{
}

void NotePad::onIndent()
{
    QString s = text->toPlainText();
    this->indent();
}

void NotePad::keyPressEvent(QKeyEvent *e)
{
    if ((e->key () == Qt::Key_Enter))
    {
        //cout << "enter pressed" << endl;
    }
}

bool NotePad::eventFilter(QObject *o, QEvent *e)
{
    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(e);

    if (e->type() == QEvent::KeyPress)
    {
        if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
        {
            return insertCharacterForKeyFiltering("\n");
        }
        else if (keyEvent->key() == Qt::Key_Greater)
        {
            return insertCharacterForKeyFiltering(">");
        }
    }
    return false;
}

void NotePad::indent()
{ 
    selectWholeLine();
    int selectionStart = text->textCursor().selectionStart();
    int selectionEnd = text->textCursor().selectionEnd();

    th->clearTabNumber();

    QString indented;
    QString s = text->toPlainText();

    QString left = s.left(selectionStart);
    QString right = s.right(s.length() - selectionEnd);

    QStringList line = s.split("\n");

    QRegExp regex("^(\\s)*");

    QTextCursor c = text->textCursor();

    c.setPosition(selectionStart);
    int upperBound = c.blockNumber();

    c.setPosition(selectionEnd);
    int lowerBound = c.blockNumber();

    for (int i = 0; i < line.length(); ++i) {
        QStringList tokens = line.at(i).split(regex);
        for (int var = 1; var < tokens.length(); ++var) {
            QString token = tokens.at(var);

            if(isCloseTag(token))
            {
                th->decrementTabNumber();
                appendTextWithBounds(&indented, upperBound, lowerBound, i, token);

            }
            else if (isOpenTag(token))
            {
                appendTextWithBounds(&indented, upperBound, lowerBound, i, token);
                th->incrementTabNumber();
            }
            else
            {
                appendTextWithBounds(&indented, upperBound, lowerBound, i, token);
            }
        }
    }
    if(selectionStart < s.length() - 1)
    {
        text->setPlainText(left.append(indented).append(right));
    }

    c.setPosition(selectionEnd);
    c.movePosition(QTextCursor::EndOfBlock);
    text->setTextCursor(c);
}

bool NotePad::insertCharacterForKeyFiltering(const QString str)
{
    QTextCursor c = text->textCursor();

    int pos = c.position();
    QString left = text->toPlainText().left(pos);
    QString right = text->toPlainText().right(text->toPlainText().length() - pos);

    QString s = left.append(str).append(right);

    text->setPlainText(s);
    c.setPosition(pos + 1);
    text->setTextCursor(c);
    this->indent();
    return true;
}

bool NotePad::isOpenTag(QString token) const
{
    QRegExp rx("<[a-zA-Z]*>");
    return rx.exactMatch(token);
}

bool NotePad::isCloseTag(QString token) const
{
    QRegExp rx("</[a-zA-Z]*>");
    return rx.exactMatch(token);
}

void NotePad::insertTabs(QString* l) const
{
    for (int i = 0; i < th->getTabNumber(); ++i) {
        l->append("    ");
    }
}

void NotePad::insertTabsOnEnterHit() const
{
    this->text->textCursor().insertText("\n");

    for (int i = 0; i < th->getTabNumber(); ++i) {
        this->text->textCursor().insertText("    ");
    }
}

void NotePad::selectWholeLine() const
{
    QTextCursor cursor = text->textCursor();
    int selectionStart = cursor.selectionStart();
    int selectionEnd = cursor.selectionEnd();

    cursor.setPosition(selectionStart);
    cursor.movePosition(QTextCursor::StartOfBlock);
    selectionStart = cursor.position();

    cursor.setPosition(selectionEnd);
    cursor.movePosition(QTextCursor::EndOfBlock);
    selectionEnd = cursor.selectionEnd();

    cursor.setPosition(selectionStart);
    cursor.setPosition(selectionEnd, QTextCursor::KeepAnchor);

    text->setTextCursor(cursor);
}

void NotePad::appendTextWithBounds(QString *indented, int upperBound, int lowerBound, int currentLine, QString toAppend)
{
    if(currentLine >= upperBound && currentLine <= lowerBound)
    {
        if(currentLine != upperBound)
        {
            indented->append("\n");
        }
        cout << "to append :" << toAppend.toStdString() << endl;
        insertTabs(indented);
        indented->append(toAppend);
    }
}
