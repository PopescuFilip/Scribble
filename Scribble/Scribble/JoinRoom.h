#pragma once

#include <QMainWindow>
#include "ui_JoinRoom.h"
#include <QPushButton>
#include <QColor>
#include "WaitingRoom.h"
#include "Profile.h"

class JoinRoom : public QMainWindow
{
	Q_OBJECT

public:
	JoinRoom(int userId, QWidget *parent = nullptr);
	~JoinRoom();

	void paintEvent(QPaintEvent* event) override;

private slots:
	void clickOnInsertButton();
	void clickOnCreateButton();
	void clickOnProfileButton();

private:
	Ui::JoinRoomClass ui;

};
