#ifndef XMLEDITOR_H
#define XMLEDITOR_H

#include <QTextEdit>
#include <QXmlStreamReader>
#include <QDomNode>
#include <vector>
#include <stack>
#include <QtXmlPatterns/QXmlSchemaValidator>
#include <QtXmlPatterns/QXmlSchema>
#include <QMutex>
#include <QWaitCondition>

using namespace std;

#include "texteditor.h"

class XmlEditor : public TextEditor
{
    Q_OBJECT
public:
    XmlEditor();

    void addDtd();

    void onNodeNameUpdate(QDomNode, QString);
    void onNodeDelete(QDomNode);
    void onNodeInsert(QDomNode, QDomNode);
    void saveNodeData(QDomNode);

    QString extractSchemaUrl();
    /**
      met à jour l'arbo et verifie si le xml est valide
      */
    void onRefreshRequest();

private slots:
    void onTextChange();

signals:
    void update();

private:
    bool dragnDropHappened;
    QString savedNodeData;
    stack<int> savedPath;

    void insertNodeText();

    bool eventFilter(QObject *o, QEvent *e);
    bool insertCharacterForKeyFiltering(const QString str);
    void updateDom();

    /**
      remplace oldName par newName dans le document
      */
    void updateNodeName(QDomNode node, QString oldName, QString newName);

    void addCloseMarkup();

};

#endif // XMLEDITOR_H
