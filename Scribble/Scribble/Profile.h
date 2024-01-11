#pragma once

#include <QMainWindow>
#include "ui_Profile.h"
#include "WaitingRoom.h"

class Profile : public QMainWindow
{
	Q_OBJECT

public:
	Profile(int username, QWidget *parent = nullptr);
	~Profile();
public:
	void clickedOnButton(int username, std::string code);
private:
	Ui::ProfileClass ui;
	int m_userId;
};
