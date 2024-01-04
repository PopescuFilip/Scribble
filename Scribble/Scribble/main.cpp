#include "Scribble.h"
#include "JoinRoom.h"
#include "WaitingRoom.h"
#include "Login.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap cursor = QPixmap("Images/Cursor.cur");
    QPixmap resizeCursor = cursor.scaled(40, 40);
    QCursor setCursor(resizeCursor, 0, 0);
    a.setOverrideCursor(setCursor);


    Login login;
    login.show();


    return a.exec();
}
