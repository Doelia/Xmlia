#include <QApplication>

using namespace std;

#include "notepad.h"

int main(int argv, char **args)
{
    QApplication app(argv, args);

    NotePad* n = new NotePad();
    n->show();

    return app.exec();
}
