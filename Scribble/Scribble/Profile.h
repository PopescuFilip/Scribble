#pragma once

#include <QMainWindow>
#include "ui_Profile.h"
#include "WaitingRoom.h"

class Profile : public QMainWindow
{
	Q_OBJECT

public:
	Profile(std::string username, QWidget *parent = nullptr);
	~Profile();
public:
	void clickedOnButton(std::string username, std::string code);
private:
	Ui::ProfileClass ui;
	std::string m_user;
};
