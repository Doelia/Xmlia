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
    connect(indentAction, SIGNAL(triggered()), this, SLOT(indent()));

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
    /*reader->clear();
    reader->addData(text->toPlainText());
    th->clearTabNumber();
    int i = 0;
    while(!reader->atEnd())
    {
        /*if(reader->hasError())
        {
            cout << "erreur" << endl;
        }


        cout << "line number : " << i << endl;
        if(reader->isStartElement())
        {
            cout << "start element : ";
            QString t = reader->name().toString();
           /* cout << t.toUtf8().constData() << endl;
            th->incrementTabNumber();
            pile->push(t);

        }
        else if(reader->isEndElement())
        {
            cout << "end element : ";
            QString t = reader->name().toString();
           // cout << t.toUtf8().constData() << endl;
           // th->decrementTabNumber();
           // indent();

        }

        reader->readNext();
        i++;
    }*/
}

void NotePad::onTextChange()
{
    //st   parse();
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
            parse();
        }
    }
    return false;
}

void NotePad::indent()
{
    th->clearTabNumber();

    QStringList indented;
    QString s = text->toPlainText();

    int selectionStart = selectLineStart(s);
    int selectionEnd = selectLineEnd(s);

    QString left = s.left(selectionStart);
    QString right = s.right(s.length() - selectionEnd);

    QStringList line = s.split("\n");

    QRegExp regex("^(\\s)+");

    int readSoFar = 0;

    for (int i = 0; i < line.length(); ++i) {
        QStringList tokens = line.at(i).split(regex);
        for (int var = 0; var < tokens.length(); ++var) {
            QString token = tokens.at(var);
            readSoFar += token.length();

            if(isCloseTag(token))
            {
                th->decrementTabNumber();
                appendTextWithBounds(readSoFar, &indented, selectionStart, selectionEnd, token);

            }
            else if (isOpenTag(token))
            {
                appendTextWithBounds(readSoFar, &indented, selectionStart, selectionEnd, token);
                th->incrementTabNumber();
            }
            else if(!token.isEmpty())
            {
                appendTextWithBounds(readSoFar, &indented, selectionStart, selectionEnd, token);
            }
        }

    }
    if(selectionStart < s.length() - 1)
    {
        text->setPlainText(left.append(indented.join("")).append(right));
    }
}

bool NotePad::isOpenTag(QString token) const
{
    QRegExp rx("^(<.*>)$");
    return rx.exactMatch(token);
}

bool NotePad::isCloseTag(QString token) const
{
    QRegExp rx("^(</.*>)$");
    return rx.exactMatch(token);
}

bool NotePad::addTabs(QStringList* l) const
{
    for (int i = 0; i < th->getTabNumber(); ++i) {
        l->append("    ");
    }
}

int NotePad::selectLineStart(QString s)
{
    QRegExp r("\n");

    int selectionStart = text->textCursor().selectionStart();

    while(selectionStart > 0 && r.indexIn(s.at(selectionStart)))
    {
        selectionStart--;
    }

    return selectionStart;
}

int NotePad::selectLineEnd(QString s)
{
    QRegExp r("\n");

    int selectionEnd = text->textCursor().selectionEnd();

    while(selectionEnd < s.length() && r.indexIn(s.at(selectionEnd)))
    {
        selectionEnd++;
    }

    return selectionEnd;
}

void NotePad::appendTextWithBounds(int readSoFar, QStringList *indented, int selectionStart, int selectionEnd, QString toAppend)
{
    if(readSoFar > selectionStart && readSoFar < selectionEnd)
    {
        indented->append("\n");
        addTabs(indented);
        indented->append(toAppend);
    }
}
