#pragma once

#include <QMainWindow>
#include "ui_WaitingRoom.h"
#include "Scribble.h"

class WaitingRoom : public QMainWindow
{
	Q_OBJECT

public:
	WaitingRoom(int username, std::string code, QWidget *parent = nullptr);
	~WaitingRoom();

	void paintEvent(QPaintEvent* event) override;

private slots:
	void clickOnStartButton();

private:
	Ui::WaitingRoomClass ui;	
	int m_userId;
	std::string m_roomCode;
};
