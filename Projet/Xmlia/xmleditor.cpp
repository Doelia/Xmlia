#include "xmleditor.h"
#include "modelexml.h"
#include "xmlfilemanager.h"

XmlEditor::XmlEditor() : TextEditor::TextEditor(new TextHighLighter(0))
{
    tabNumber = 0;
    hasError = false;
    text->installEventFilter(this);
    QStringList l;
    l << "xml" << "root";
    completer = new QCompleter(l);
    text->setText("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\n<root>\n</root>");

    connect(text, SIGNAL(textChanged()), this, SLOT(onTextChange()));
}

void XmlEditor::addDtd()
{
    this->removeSchema();
    if(extractSchemaUrl().size() == 0)
    {
        QXmlStreamReader xml(text->toPlainText());
        QTextCursor c = text->textCursor();

        while(!xml.atEnd())
        {
            if(xml.isStartElement())
            {
                moveCursorToLineAndColumn(&c, xml.lineNumber() - 1, xml.columnNumber() - 1, false);
                QString link("\nxmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\nxsi:noNamespaceSchemaLocation=\"");
                link.append(XmlFileManager::getFileManager()->getSchemaName()).append("\"");
                c.insertText(link);
                text->setTextCursor(c);
                emit log(QString("Linked xml file to : "+ XmlFileManager::getFileManager()->getCurrentSchema()), QColor("black"));
                return;
            }
            xml.readNext();
        }
    }
}

void XmlEditor::removeSchema()
{
    QString s(text->toPlainText());
    QRegExp r("\n*xmlns:xsi.*=\".*\.xsd\"\n*");
    s.remove(r);
    text->setText(s);
}

bool XmlEditor::updateNodeName(int *nbFound, int *begin, int *end, QTextCursor *c, QString oldName, QString newName, QXmlStreamReader *xml)
{
    if(*nbFound == 0)
    {
        (*nbFound)++;
        moveCursorToLineAndColumn(c, xml->lineNumber() - 1, xml->columnNumber() - oldName.size() - 2, false);
        c->setPosition(c->position() + oldName.size() + 1, QTextCursor::KeepAnchor);
        *begin = c->selectionStart();
        *begin = goToNodeStart(*begin, text->toPlainText());
        *end = c->selectionEnd();
        return false;
    }
    else if (*nbFound == 1 && xml->name().size() > 0)
    {
        moveCursorToLineAndColumn(c, xml->lineNumber() - 1, xml->columnNumber() - oldName.size() - 2, false);
        c->setPosition(c->position() + oldName.size() + 1, QTextCursor::KeepAnchor);

        QString t = c->selectedText();

        if(c->position() > *end)
        {
            t.replace(oldName, newName);
            c->removeSelectedText();
            c->insertText(t);
        }

        c->setPosition(*begin);
        c->setPosition(*end, QTextCursor::KeepAnchor);
        t = c->selectedText();
        t.replace(oldName, newName);
        c->removeSelectedText();
        c->insertText(t);

        text->setTextCursor(*c);
        return true;
    }
    return false;
}

bool XmlEditor::deleteNode(int *nbFound, int *begin, int *end, QTextCursor *c, QString oldName, QString newName, QXmlStreamReader *xml)
{
    if(*nbFound == 0)
    {
        moveCursorToLineAndColumn(c, xml->lineNumber() - 1, xml->columnNumber() - 1, true);
        *begin = c->position();
        *begin = goToNodeStart(*begin, text->toPlainText());
        (*nbFound)++;
        return false;

    }
    else if (*nbFound == 1 && xml->name().size() > 0)
    {
        moveCursorToLineAndColumn(c, xml->lineNumber() - 1, xml->columnNumber(), true);
        *end = c->position();
        c->setPosition(*begin, QTextCursor::MoveAnchor);
        c->setPosition(*end, QTextCursor::KeepAnchor);
        c->removeSelectedText();
        c->movePosition(QTextCursor::StartOfLine);
        c->movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
        QRegExp q("\\S+");
        if(q.indexIn(c->selectedText()) == -1)
        {
            c->setPosition(c->position() + 1, QTextCursor::KeepAnchor);
            c->removeSelectedText();
        }
        else
        {
            c->setPosition(*begin);
        }
        text->setTextCursor(*c);
        return true;
    }
    return false;
}

bool XmlEditor::saveNodeData(int *nbFound, int *begin, int *end, QTextCursor *c, QString oldName, QString newName, QXmlStreamReader *xml)
{
    if(*nbFound == 0)
    {
        (*nbFound)++;
        moveCursorToLineAndColumn(c, xml->lineNumber() - 1, xml->columnNumber() - 1, false);
        *begin = c->position();
        *begin = goToNodeStart(*begin, text->toPlainText());
        return false;
    }
    else if (*nbFound == 1 && xml->name().size() > 0)
    {
        moveCursorToLineAndColumn(c, xml->lineNumber() - 1, xml->columnNumber(), true);
        *end = c->position();
        c->setPosition(*begin, QTextCursor::MoveAnchor);
        c->setPosition(*end, QTextCursor::KeepAnchor);
        savedNodeData = c->selectedText();
        cout << "data : " << savedNodeData.toStdString() << endl;
        return true;
    }
    return false;
}


bool XmlEditor::validateAndRefreshTree()
{
    //emit un signal si le xml est valide
    resetLinesNumber();
    QXmlStreamReader xml(text->toPlainText());
    hasError = false;


    while(!xml.atEnd())
    {
        xml.readNext();
        if(xml.hasError())
        {
            hasError = true;
        }
    }

    if(!hasError)
    {
        updateDom();
        emit log("Syntaxe XML valide", QColor("green"));

        QXmlSchema schema;
        QString url(extractSchemaUrl());


        cout << "url extracted : " << url.toStdString() << endl;

        //si le xml contient une url valide vers un schema
        if(url.size() > 1)
        {
            XmlFileManager::getFileManager()->setCurrentSchema(url);
            XmlFileManager::getFileManager()->openDTD();
            schema.load(QString("file://").append(url));
            if (schema.isValid())
            {
                cout << "schema valide" << endl;
                emit log("Schema XSD valide", QColor("green"));
                QXmlSchemaValidator validator(schema);
                validator.setMessageHandler(mh);
                if (validator.validate(this->getText().toUtf8(), QUrl(XmlFileManager::getFileManager()->getCurrentSchema())))
                {
                    emit log("Semantique XML valide", QColor("green"));
                    return true;
                }
            }
            return true;
        }
        emit log("Schema XSD invalide, est-il manquant ou invalide ?", QColor("orange"));
    }
    else
    {
        emit error(xml.lineNumber() - 1);
        emit log("Erreur ligne " + QString::number(xml.lineNumber()) + " : " + xml.errorString(), QColor("red"));
    }
    return false;
}

void XmlEditor::setSavedPath(stack<int> path)
{
    savedPath = path;
}

void XmlEditor::updateDom()
{
    XmlFileManager::getFileManager()->getModele()->update(this->text->toPlainText());
    emit update();
}

void XmlEditor::parseDom(QDomNode &target, QString oldName, QString newName,
                         bool (XmlEditor::*function)(int *nbFound, int *begin,
                                                     int *end, QTextCursor *c, QString oldName, QString newName, QXmlStreamReader *xml))
{
    stack<int> st;
    if(!savedPath.empty())
    {
        cout << "going to replace" << endl;
        st = savedPath;
        savedPath = stack<int>();
    }
    else
    {
        st = ModeleXml::pathFromRoot(target);
    }

    vector<int> nodePath;

    while(!st.empty())
    {
        nodePath.push_back(st.top());
        st.pop();
    }

    nodePath[0]++;
    vector<int> path;
    path.push_back(0);
    QXmlStreamReader xml(text->toPlainText());
    QXmlStreamReader::TokenType lastToken;
    lastToken = QXmlStreamReader::NoToken;
    QTextCursor c = text->textCursor();

    int begin;
    int end;
    int nbFound = 0;

    xml.readNext();
    while(!xml.atEnd())
    {
        if(xml.isStartElement())
        {
            if(lastToken == QXmlStreamReader::StartElement)
            {
                path.push_back(0);
            }
            else
            {
                path[path.size() - 1]++;
            }
        }
        else if(xml.isEndElement())
        {
            if(lastToken == QXmlStreamReader::EndElement)
            {
                path.pop_back();
            }
        }

        if(cmpVectors(path, nodePath))
        {
            if((this->*function)(&nbFound, &begin, &end, &c, oldName, newName, &xml))
            {
                return;
            }
        }
        if(xml.tokenType() == QXmlStreamReader::StartElement ||
                xml.tokenType() == QXmlStreamReader::StartDocument ||
                xml.tokenType() == QXmlStreamReader::EndDocument ||
                xml.tokenType() == QXmlStreamReader::EndElement)
        {
            lastToken = xml.tokenType();
        }
        xml.readNext();
    }
}

int XmlEditor::goToNodeStart(int begin, QString s)
{
    QString open = "<";
    while(open.compare(s.at(begin)) != 0)
    {
        begin--;
    }
    return begin;
}

bool XmlEditor::cmpVectors(vector<int> v1, vector<int> v2)
{
    if(v1.size() == v2.size())
    {
        for (int i = 0; i < v1.size(); ++i) {
            if(v2[i] != v1[i])
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

void XmlEditor::moveCursorToLineAndColumn(QTextCursor *c, int line, int column, bool keepAnchor)
{
    c->setPosition(0);
    c->movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, line);
    c->setPosition(c->position() + column, (keepAnchor)?(QTextCursor::KeepAnchor):(QTextCursor::MoveAnchor));
}

void XmlEditor::addCloseMarkup()
{
    QTextCursor c = text->textCursor();
    int pos = c.position() - 1;

    QString open = "<";
    QString error1 = "\n";
    QString error2 = "/";
    QString error3 = ">";

    QString s = text->toPlainText();
    QChar at;

    while(true)
    {
        at = s.at(pos);
        if(!open.compare(at))
        {
            QString markup = s.mid(pos + 1, c.position() - pos - 1);
            markup = markup.split(" ").at(0);
            if(markup.length() > 0)
            {
                QString toAdd = "></";
                toAdd.append(markup).append(">");
                c.insertText(toAdd);
                c.setPosition(c.position() -  markup.length() - 3);
                c.setPosition(c.position() + markup.length() + 3, QTextCursor::KeepAnchor);
                text->setTextCursor(c);
            }
            return;
        }
        else if (!error1.compare(at) || !error2.compare(at) || !error3.compare(at))
        {
            cout << s.mid(pos + 1, c.position()).toStdString() << endl;
            c.insertText(">");
            text->setTextCursor(c);
            return;
        }
        pos--;
    }
}

QString XmlEditor::extractSchemaUrl()
{
    QString s(text->toPlainText());
    QStringList l(s.split("xsi:noNamespaceSchemaLocation=\""));
    if(l.size() > 1)
    {
        s = l.at(1).split("\"").at(0);
        return XmlFileManager::getFileManager()->getCurrentFilePath().append("/").append(s);
    }

    l = s.split("xsi:SchemaLocation=\"");
    if(l.size() > 1)
    {
        emit log("Cannot process http requests yet, XML will not be checked", QColor("orange"));
    }
    return "";
}

bool XmlEditor::eventFilter(QObject *o, QEvent *e)
{
    emit cursorInfo(text->textCursor().block().blockNumber(), text->textCursor().positionInBlock());
    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(e);

    if (e->type() == QEvent::KeyPress)
    {
        if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
        {
            return insertCharacterForKeyFiltering("\n");
        }
        else if (keyEvent->key() == Qt::Key_Greater)
        {
            addCloseMarkup();
            return true;
        }
        else if (keyEvent->key() == Qt::Key_Tab)
        {
            this->indent();
            return true;
        }
        else if (keyEvent->key() == Qt::Key_Control)
        {
            //currentNode();
        }
    }
    return false;
}

bool XmlEditor::insertCharacterForKeyFiltering(const QString str)
{
    QTextCursor c = text->textCursor();

    int pos = c.position();
    c.insertText(str);
    int oldPos = c.position();
    c.setPosition(pos);
    c.movePosition(QTextCursor::StartOfLine);
    pos = c.position();

    QString s = text->toPlainText();
    QString space = " ";
    int nbSpace = 0;

    while(!s.mid(pos, 1).compare(space))
    {
        nbSpace++;
        pos++;
    }

    c.setPosition(oldPos);
    c.insertText(tabsString(nbSpace/NB_SPACE));
    text->setTextCursor(c);

    return true;
}

void XmlEditor::onTextChange()
{
    if(hasError)
    {
        TextEditor::resetLinesNumber();
    }
}


bool XmlEditor::insertNodeText(int *nbFound, int *begin, int *end, QTextCursor *c, QString oldName, QString newName, QXmlStreamReader *xml)
{
    cout << "inserting : " << savedNodeData.toStdString() << endl;
    QString slash("/");
    bool isSingle = false;
    moveCursorToLineAndColumn(c, xml->lineNumber() - 1, xml->columnNumber() - 1, false);
    if(!slash.compare(text->toPlainText().at(c->position() - 1)))
    {
        c->setPosition(c->position() - 1, QTextCursor::MoveAnchor);
        isSingle = true;
    }
    c->insertText(QString(">").append(savedNodeData));

    if(isSingle)
    {
        c->insertText(QString("</").append(xml->name().toString()));
    }
    c->setPosition(c->position() + 1, QTextCursor::KeepAnchor);
    c->removeSelectedText();
    text->setTextCursor(*c);
    return true;
}
