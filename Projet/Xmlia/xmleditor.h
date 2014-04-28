#ifndef XMLEDITOR_H
#define XMLEDITOR_H

#include <QTextEdit>
#include <QXmlStreamReader>
#include <QDomNode>
#include <vector>
#include <stack>
#include <QtXmlPatterns/QXmlSchemaValidator>
#include <QtXmlPatterns/QXmlSchema>

using namespace std;

#include "texteditor.h"

class XmlEditor : public TextEditor
{
    Q_OBJECT
public:
    XmlEditor();

    void addDtd();
    void removeSchema();

    bool onNodeNameUpdate(int *nbFound, int *begin, int *end, QTextCursor *c, QString oldName, QString newName, QXmlStreamReader *xml);
    bool onNodeDelete(int *nbFound, int *begin, int *end, QTextCursor *c, QString oldName, QString newName, QXmlStreamReader *xml);
    bool saveNodeData(int *nbFound, int *begin, int *end, QTextCursor *c, QString oldName, QString newName, QXmlStreamReader *xml);
    bool insertNodeText(int *nbFound, int *begin, int *end, QTextCursor *c, QString oldName, QString newName, QXmlStreamReader *xml);

    void parseDom(QDomNode &target, QString oldName, QString newName, bool (XmlEditor::*function)
                  (int *nbFound, int *begin, int *end, QTextCursor *c, QString oldname, QString newname, QXmlStreamReader *xml));

    QString extractSchemaUrl();
    /**
      met à jour l'arbo et verifie si le xml est valide
      */
    bool onRefreshRequest();

    void setSavedPath(stack<int> path);

private slots:
    void onTextChange();

signals:
    void update();

private:
    QString savedNodeData;
    stack<int> savedPath;


    bool eventFilter(QObject *o, QEvent *e);
    bool insertCharacterForKeyFiltering(const QString str);
    void updateDom();


    int goToNodeStart(int, QString);
    bool cmpVectors(vector<int>, vector<int>);
    void moveCursorToLineAndColumn(QTextCursor* c, int line, int column, bool keepAnchor);

    void addCloseMarkup();

};

#endif // XMLEDITOR_H
