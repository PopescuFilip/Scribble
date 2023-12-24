#pragma once

#include <QMainWindow>
#include "ui_EndScreen.h"

class EndScreen : public QMainWindow
{
	Q_OBJECT

public:
	EndScreen();
	EndScreen(std::string username, QWidget *parent = nullptr);
	~EndScreen();

private:
	Ui::EndScreenClass ui;
	std::string m_user;
};
