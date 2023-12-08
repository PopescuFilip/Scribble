#include "Scribble.h"
#include "JoinRoom.h"
#include "WaitingRoom.h"
#include "Login.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Login login;
    login.show();

    return a.exec();
}
