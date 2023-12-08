#pragma once

#include <QMainWindow>
#include "ui_WaitingRoom.h"

class WaitingRoom : public QMainWindow
{
	Q_OBJECT

public:
	WaitingRoom(QWidget *parent = nullptr);
	~WaitingRoom();

	void paintEvent(QPaintEvent* event) override;

private slots:
	void clickOnStartButton();

private:
	Ui::WaitingRoomClass ui;	
	std::string m_user;
};
