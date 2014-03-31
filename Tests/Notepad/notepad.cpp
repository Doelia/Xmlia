#include "notepad.h"

NotePad::NotePad()
{
    this->text = new QTextEdit();
    this->th = new TextHighLighter(text->document());
    this->reader = new QXmlStreamReader();

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

    this->tabNumber = 0;

    setWindowTitle("superman");
    this->resize(800, 600);
}

void NotePad::quit()
{
    qApp->quit();
}

void NotePad::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
                                                    tr("Text Files (*.txt);;Xml Files (*.xml)"));

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
                                                    tr("Text Files (*.txt);;Xml Files (*.xml)"));

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

    tabNumber = 0;

    QTextCursor c = text->textCursor();

    c.setPosition(selectionStart);
    int upperBound = c.blockNumber();
    c.setPosition(selectionEnd);
    int lowerBound = c.blockNumber();

    QString s = text->toPlainText();
    QStringList line = s.split("\n");

    QXmlStreamReader xml(this->text->toPlainText());

    int last = 0;

    while(!xml.atEnd())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        for (int var = last; var < xml.lineNumber(); ++var) {
            indentLineWithBounds(&line, var, upperBound, lowerBound);
        }

        if(token == QXmlStreamReader::StartElement)
        {
            last = xml.lineNumber();
            indentLineWithBounds(&line, xml.lineNumber() - 1, upperBound, lowerBound);
            tabNumber++;
        }
        else if(token == QXmlStreamReader::EndElement)
        {
            last = xml.lineNumber();
            tabNumber--;
            indentLineWithBounds(&line, xml.lineNumber() - 1, upperBound, lowerBound);
        }


    }

    if(selectionStart < s.length() - 1)
    {
        text->setPlainText(line.join("\n"));
    }
    c.setPosition(selectionEnd);
    c.movePosition(QTextCursor::EndOfBlock);
    text->setTextCursor(c);
}

void NotePad::indentLineWithBounds(QStringList *list, int line, int upperBound, int lowerBound)
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

QString NotePad::tabsString(int n) const
{
    QString l;
    for (int i = 0; i < n; i++) {
        l.append("        ");
    }
    return l;
}

void NotePad::insertTabsOnEnterHit() const
{
    this->text->textCursor().insertText("\n");

    for (int i = 0; i < tabNumber; ++i) {
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
