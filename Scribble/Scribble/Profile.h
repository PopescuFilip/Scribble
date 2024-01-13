#pragma once

#include <QMainWindow>
#include "ui_Profile.h"
#include "WaitingRoom.h"

class Profile : public QMainWindow
{
	Q_OBJECT

public:
	Profile(int userId, QWidget *parent = nullptr);
	~Profile();
public:
	void ShowScores();
private:
	Ui::ProfileClass ui;
	int m_userId;
};
