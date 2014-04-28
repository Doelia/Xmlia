#include "xmleditor.h"
#include "modelexml.h"
#include "xmlfilemanager.h"

XmlEditor::XmlEditor() : TextEditor::TextEditor(new TextHighLighter(0))
{
    tabNumber = 0;
    hasError = false;
    text->installEventFilter(this);
    completer = new QCompleter();
    text->setText("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\n<root>\n</root>");

    connect(text, SIGNAL(textChanged()), this, SLOT(onTextChange()));
}

void XmlEditor::addDtd()
{
    //TODO  enlever l'ancien lien

    this->removeSchema();
    if(extractSchemaUrl().size() == 0)
    {
        QXmlStreamReader xml(text->toPlainText());
        QTextCursor c = text->textCursor();

        while(!xml.atEnd())
        {
            if(xml.isStartElement())
            {
                c.setPosition(0);
                c.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, xml.lineNumber()-1);
                c.setPosition(c.position() + xml.columnNumber() - 1);
                QString link("\nxmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\nxsi:noNamespaceSchemaLocation=\"");
                link.append(XmlFileManager::getFileManager()->getSchemaName()).append("\"");
                c.insertText(link);
                text->setTextCursor(c);
                emit log(QString("Linked xml file to : "+ XmlFileManager::getFileManager()->getCurrentFileName()), QColor("black"));
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
    //s.remove(XmlFileManager::getFileManager()->getSchemaName().append("\""));
    text->setText(s);
}

void XmlEditor::onNodeNameUpdate(QDomNode n, QString newName)
{
    QString oldName = n.nodeName();

    updateNodeName(n, oldName, newName);
    this->th->rehighlight();
}

void XmlEditor::onNodeDelete(QDomNode n)
{


    cout << "XmlEditor::onNodeDelete()" << endl;
    auto vequal = [](vector<int> v1, vector<int> v2)->bool
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
};

auto goToNodeStart = [] (int *begin, QString s)->void
{
        QString open = "<";
while(open.compare(s.at(*begin)) != 0)
{
    (*begin)--;
}
};

stack<int> st = ModeleXml::pathFromRoot(n);
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

    if(vequal(path, nodePath))
    {
        if(nbFound == 0)
        {
            nbFound++;
            c.setPosition(0);
            c.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, xml.lineNumber()-1);
            c.setPosition(c.position() + xml.columnNumber() - 1, QTextCursor::KeepAnchor);
            begin = c.position();
            goToNodeStart(&begin, text->toPlainText());
        }
        else if (nbFound == 1 && xml.name().size() > 0)
        {
            c.setPosition(0);
            c.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, xml.lineNumber()-1);
            c.setPosition(c.position() + xml.columnNumber(), QTextCursor::KeepAnchor);
            end = c.position();
            c.setPosition(begin, QTextCursor::MoveAnchor);
            c.setPosition(end, QTextCursor::KeepAnchor);
            c.removeSelectedText();
            c.movePosition(QTextCursor::StartOfLine);
            c.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
            QRegExp q("\\S+");
            if(q.indexIn(c.selectedText()) == -1)
            {
                c.setPosition(c.position() + 1, QTextCursor::KeepAnchor);
                c.removeSelectedText();
            }
            else
            {
                c.setPosition(begin);
            }
            text->setTextCursor(c);
            if(dragnDropHappened)
            {
                dragnDropHappened = false;
                insertNodeText();
            }
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

cout << "XmlEditor::onNodeDelete() end" << endl;
}

void XmlEditor::onNodeInsert(QDomNode parent, QDomNode n)
{

    cout << "XmlEditor::onNodeInsert" << endl;
    savedPath = ModeleXml::pathFromRoot(parent);
    dragnDropHappened = true;
}

void XmlEditor::saveNodeData(QDomNode n)
{

    cout << "XmlEditor::saveNodeData" << endl;
    auto vequal = [](vector<int> v1, vector<int> v2)->bool
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
};

auto goToNodeStart = [] (int *begin, QString s)->void
{
        QString open = "<";
while(open.compare(s.at(*begin)) != 0)
{
    (*begin)--;
}
};

stack<int> st = ModeleXml::pathFromRoot(n);
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

    if(vequal(path, nodePath))
    {
        if(nbFound == 0)
        {
            nbFound++;
            c.setPosition(0);
            c.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, xml.lineNumber()-1);
            c.setPosition(c.position() + xml.columnNumber() - 1, QTextCursor::KeepAnchor);
            begin = c.position();
            goToNodeStart(&begin, text->toPlainText());
        }
        else if (nbFound == 1 && xml.name().size() > 0)
        {
            c.setPosition(0);
            c.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, xml.lineNumber()-1);
            c.setPosition(c.position() + xml.columnNumber(), QTextCursor::KeepAnchor);
            end = c.position();
            c.setPosition(begin, QTextCursor::MoveAnchor);
            c.setPosition(end, QTextCursor::KeepAnchor);
            savedNodeData = c.selectedText();
            cout << "data : " << savedNodeData.toStdString() << endl;
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


bool XmlEditor::onRefreshRequest()
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

void XmlEditor::updateNodeName(QDomNode n, QString oldName, QString newName)
{
    auto vequal = [](vector<int> v1, vector<int> v2)->bool
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
};

auto goToNodeStart = [] (int *begin, QString s)->void
{
        QString open = "<";
while(open.compare(s.at(*begin)) != 0)
{
    (*begin)--;
}
};

stack<int> st = ModeleXml::pathFromRoot(n);
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

    if(vequal(path, nodePath))
    {
        if(nbFound == 0)
        {
            nbFound++;
            c.setPosition(0);
            c.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, xml.lineNumber()-1);
            c.setPosition(c.position() + xml.columnNumber() - oldName.size() - 2, QTextCursor::MoveAnchor);
            c.setPosition(c.position() + oldName.size() + 1, QTextCursor::KeepAnchor);
            begin = c.selectionStart();
            goToNodeStart(&begin, text->toPlainText());
            end = c.selectionEnd();

        }
        else if (nbFound == 1 && xml.name().size() > 0)
        {
            c.setPosition(0);
            c.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, xml.lineNumber()-1);
            c.setPosition(c.position() + xml.columnNumber() - oldName.size() - 2, QTextCursor::MoveAnchor);
            c.setPosition(c.position() + oldName.size() + 1, QTextCursor::KeepAnchor);

            QString t = c.selectedText();

            if(c.position() > end)
            {
                t.replace(oldName, newName);
                c.removeSelectedText();
                c.insertText(t);
            }

            c.setPosition(begin);
            c.setPosition(end, QTextCursor::KeepAnchor);
            t = c.selectedText();
            t.replace(oldName, newName);
            c.removeSelectedText();
            c.insertText(t);

            text->setTextCursor(c);
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

void XmlEditor::updateDom()
{
    XmlFileManager::getFileManager()->getModele()->update(this->text->toPlainText());
    emit update();
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


void XmlEditor::insertNodeText()
{
    auto vequal = [](vector<int> v1, vector<int> v2)->bool
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
};

stack<int> st = savedPath;
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

    if(vequal(path, nodePath))
    {
        QString slash("/");
        bool isSingle = false;
        c.setPosition(0);
        c.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, xml.lineNumber()-1);
        c.setPosition(c.position() + xml.columnNumber() - 1, QTextCursor::MoveAnchor);
        if(!slash.compare(text->toPlainText().at(c.position() - 1)))
        {
            c.setPosition(c.position() - 1, QTextCursor::MoveAnchor);
            isSingle = true;
        }
        c.insertText(QString(">").append(savedNodeData));

        if(isSingle)
        {
            c.insertText(QString("</").append(xml.name().toString()));
        }
        c.setPosition(c.position() + 1, QTextCursor::KeepAnchor);
        c.removeSelectedText();
        text->setTextCursor(c);
        return;
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
