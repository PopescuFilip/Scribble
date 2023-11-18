#include "Scribble.h"
#include "JoinRoom.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Scribble w;
    qDebug() << "Hello world";
    w.show();

    JoinRoom join;
    join.paintEvent();
    join.show();

    return a.exec();
}
