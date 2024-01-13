#pragma once

#include <QMainWindow>
#include "ui_EndScreen.h"
#include "Routes.h"
#include <sstream>
#include <qmessagebox.h>

class EndScreen : public QMainWindow
{
	Q_OBJECT

public:
	EndScreen(const std::string& roomCode, QWidget *parent = nullptr);
	~EndScreen();

public:
	void ShowRanking();

private:
	Ui::EndScreenClass ui;
	std::string m_roomCode;
};
