#pragma once

#include <QMainWindow>
#include "ui_Login.h"

class Login : public QMainWindow
{
	Q_OBJECT

public:
	Login(QWidget *parent = nullptr);
	~Login();

private slots:
	void clickedOnLogInButton();
	void clickedOnRegisterButton();

private:
	Ui::LoginClass ui;
	std::string m_user;
};
