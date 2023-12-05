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

	void paintEvent(QPaintEvent* event) override;

private:
	Ui::JoinRoomClass ui;
	std::string m_user;
};
