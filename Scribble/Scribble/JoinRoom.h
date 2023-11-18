#pragma once

#include <QMainWindow>
#include "ui_JoinRoom.h"
#include <QPushButton>
#include <QColor>

class JoinRoom : public QMainWindow
{
	Q_OBJECT

public:
	JoinRoom(QWidget *parent = nullptr);
	~JoinRoom();

	void paintEvent();

private:
	Ui::JoinRoomClass ui;
};
