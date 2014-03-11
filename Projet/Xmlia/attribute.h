#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <QString>

/**
  Structure représentant un attribut dans un noeud XML
**/

class Attribute
{
public:
    QString attribut;
    QString value;
    Attribute(QString attribut, QString value);
};

#endif // ATTRIBUTE_H
