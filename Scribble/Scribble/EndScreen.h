#pragma once

#include <QMainWindow>
#include "ui_EndScreen.h"

class EndScreen : public QMainWindow
{
	Q_OBJECT

public:
	EndScreen(int username, QWidget *parent = nullptr);
	~EndScreen();

private:
	Ui::EndScreenClass ui;
	int m_userId;
	std::string m_roomCode;
};
