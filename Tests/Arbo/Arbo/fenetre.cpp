#include "fenetre.h"

Fenetre::Fenetre()
{
    setFixedSize(300, 180);
    QVBoxLayout *layout = new QVBoxLayout;

    Arbo* arbo = new Arbo();

    layout->addWidget(arbo->getVue());
    this->setLayout(layout);

}
