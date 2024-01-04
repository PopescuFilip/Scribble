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
		"border-width: 2px;"
		"border - style: dashed;"
		"border - color: white;"
		"color: purple;"
		"padding: 5px 5px;"
		"text-align: center;"
		"text-decoration: none;"
		"font-size: 12px;"
		"border-radius: 1px;"
		"font-weight: bold;"
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

