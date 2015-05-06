#include "imago.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Imago w;

    w.show();

    return a.exec();
}
