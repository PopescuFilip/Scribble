#pragma once

#include <QMainWindow>
#include "ui_WaitingRoom.h"
#include "Scribble.h"
#include <qtimer.h>

class WaitingRoom : public QMainWindow
{
	Q_OBJECT

public:
	WaitingRoom(int username, std::string code, bool isOwner = false, QWidget *parent = nullptr);
	~WaitingRoom();

	void paintEvent(QPaintEvent* event) override;
	void ShowPlayers();

private slots:
	void clickOnStartButton();
	void checkGameState();

private:
	Ui::WaitingRoomClass ui;	
	int m_userId;
	bool m_isOwner;
	std::string m_roomCode;
	QTimer m_refreshTimer;
};
