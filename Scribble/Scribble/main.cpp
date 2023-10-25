#include "Scribble.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Scribble w;
    qDebug() << "Hello world";
    w.show();
    return a.exec();
}
