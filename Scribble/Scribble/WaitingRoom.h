#pragma once

#include <QMainWindow>
#include "ui_WaitingRoom.h"

class WaitingRoom : public QMainWindow
{
	Q_OBJECT

public:
	WaitingRoom(QWidget *parent = nullptr);
	~WaitingRoom();

private:
	Ui::WaitingRoomClass ui;
};
