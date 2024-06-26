#include "Login.h"
#include <QPixmap>
#include<qmainwindow.h>
#include <qmessagebox.h>

Login::Login(QWidget *parent)
	: QMainWindow{ parent }
{
	ui.setupUi(this);

	QPixmap background("Images/LogInBackground.png");
	background = background.scaled(1280, 720, Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, background);
	setPalette(palette);

	setFixedSize(1280, 720);
	setGeometry(140, 70, 2560, 1440);

	connect(ui.pushButtonLogIn, SIGNAL(clicked()), this, SLOT(clickedOnLogInButton()));
	connect(ui.pushButtonRegister, SIGNAL(clicked()), this, SLOT(clickedOnRegisterButton()));
}

Login::~Login()
{
}

void Login::clickedOnLogInButton()
{
	std::string user{ ui.lineEditUser->text().toUtf8().constData() };
	std::string password{ ui.lineEditPassword->text().toUtf8().constData() };
	
	qDebug() << user;
	qDebug() << password;

	cpr::Response response{ CheckUser(user,password) }; 

	if (response.status_code != 200)
	{
		ui.lineEditUser->clear();
		ui.lineEditPassword->clear();
		QMessageBox::warning(this, "Login", "Incorrect user or password");
		return;
	}

	qDebug() << response.text;
	int userId{ std::stoi(response.text) };

	close();
	JoinRoom* newWindow = new JoinRoom{ userId };
	newWindow->show();
}

void Login::clickedOnRegisterButton()
{
	std::string user{ ui.lineEditUser->text().toUtf8().constData() };
	std::string password{ ui.lineEditPassword->text().toUtf8().constData() };

	qDebug() << user;
	qDebug() << password;

	cpr::Response response{ AddUser(user,password) };

	if (response.status_code != 200)
	{
		ui.lineEditUser->clear();
		ui.lineEditPassword->clear();
		QMessageBox::warning(this, "Register", "Username is taken");
		return;
	}

	qDebug() << response.text;
	int userId{ std::stoi(response.text) };

	close();
	JoinRoom* newWindow = new JoinRoom{ userId };
	newWindow->show();
}

