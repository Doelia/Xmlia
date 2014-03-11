#ifndef FENETRE_H
#define FENETRE_H

#include "arbo.h"

class Fenetre : public QWidget
{
private:
    Arbo* arbo;
public:
    Fenetre();
};

#endif // FENETRE_H
