#pragma once

#include <QMainWindow>
#include "ui_Profile.h"

class Profile : public QMainWindow
{
	Q_OBJECT

public:
	Profile(QWidget *parent = nullptr);
	~Profile();

private:
	Ui::ProfileClass ui;
	std::string m_user;
};
