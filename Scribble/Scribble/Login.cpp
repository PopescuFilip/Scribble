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

	QString buttonStyle = "QPushButton {"
		"background-color: #4CAF50;"
		"border: none;"
		"color: purple;"
		"padding: 10px 20px;"
		"text-align: center;"
		"text-decoration: none;"
		"font-size: 16px;"
		"border-radius: 5px;"
		"}"
		"QPushButton:hover {"
		"background-color: #45a049;"
		"}";

	ui.pushButtonLogin->setStyleSheet(buttonStyle);
	ui.pushButtonRegister->setStyleSheet(buttonStyle);

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

