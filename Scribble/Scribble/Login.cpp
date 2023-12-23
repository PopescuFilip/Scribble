#include "Login.h"
#include <QPixmap>

Login::Login()
{
}

Login::Login(std::string username, QWidget *parent)
	: QMainWindow(parent),
	m_user(username)
{
	ui.setupUi(this);

	QPixmap background("Images/Background.png");
	background = background.scaled(1280, 720, Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, background);
	setPalette(palette);
	setFixedSize(1280, 720);
	setGeometry(140, 70, 2560, 1440);

	connect(ui.pushButtonLogin, SIGNAL(clicked()), this, SLOT(clickedOnLogInButton()));
	connect(ui.pushButtonRegister, SIGNAL(clicked()), this, SLOT(clickedOnRegisterButton()));

}

Login::~Login()
{
}

void Login::clickedOnLogInButton()
{
	close();
	JoinRoom* newWindow = new JoinRoom();
	newWindow->show();
}

void Login::clickedOnRegisterButton()
{
	close();
	m_join.show();
}

