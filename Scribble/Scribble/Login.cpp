#include "Login.h"
#include <QPixmap>
#include<qmainwindow.h>

//Login::Login()
//{
//}

Login::Login(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QPixmap background("Images/Background.png");
	background = background.scaled(1280, 720, Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, background);
	setPalette(palette);

	showFullScreen();

	connect(ui.pushButtonLogin, SIGNAL(clicked()), this, SLOT(clickedOnLogInButton()));
	connect(ui.pushButtonRegister, SIGNAL(clicked()), this, SLOT(clickedOnRegisterButton()));

}

Login::~Login()
{
}

void Login::clickedOnLogInButton()
{
	close();
	JoinRoom* newWindow = new JoinRoom(m_user);
	newWindow->show();
}

void Login::clickedOnRegisterButton()
{
	close();
	JoinRoom* newWindow = new JoinRoom(m_user);
	newWindow->show();
}

