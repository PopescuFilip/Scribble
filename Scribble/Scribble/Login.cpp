#include "Login.h"
#include <QPixmap>

Login::Login(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QPixmap background("Images/LogInBackground.png");
	background = background.scaled(1280, 720, Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, background);
	setPalette(palette);
	setFixedSize(1280, 720);
	setGeometry(140, 70, 2560, 1440);

	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(clickedOnRegisterButton()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(clickedOnLogInButton()));

}

Login::~Login()
{
}

void Login::clickedOnLogInButton()
{
	close();
	m_join.show();
}

void Login::clickedOnRegisterButton()
{
	close();
	m_join.show();
}

