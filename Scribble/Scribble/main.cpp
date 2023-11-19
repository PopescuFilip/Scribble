#include "Scribble.h"
#include "JoinRoom.h"
#include "WaitingRoom.h"
#include "Login.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Scribble w;
    qDebug() << "Hello world";
    w.show();

    Login login;
    login.show();

    return a.exec();
}
