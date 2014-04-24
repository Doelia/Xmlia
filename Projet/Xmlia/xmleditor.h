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

    /**
      indente le texte
      */
    void indent();
    void addDtd();

    void onNodeNameUpdate(QDomNode, QString);
    void onNodeDelete(QDomNode);

    /**
      met à jour l'arbo et verifie si le xml est valide
      */
    void onRefreshRequest();

private slots:
    void onTextChange();

signals:
    void update();

private:
    int NB_SPACE = 8;
    int tabNumber;

    void keyPressEvent(QKeyEvent *e);
    bool eventFilter(QObject *o, QEvent *e);

    bool insertCharacterForKeyFiltering(const QString str);

    void updateDom();

    /**
      indente le texte sélectionné par l'utilisateur (entre upperBound et lowerBound)
      */
    void indentLineWithBounds(QStringList *list, int line, int upperBound, int lowerBound);

    /**
      @return la ligne indentée de n tab
      */
    QString tabsString(int n) const;

    /**
      remplace oldName par newName dans le document
      */
    void updateNodeName(QDomNode node, QString oldName, QString newName);

    void addCloseMarkup();
};

#endif // XMLEDITOR_H
