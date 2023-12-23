#pragma once

#include <QMainWindow>
#include "ui_JoinRoom.h"
#include <QPushButton>
#include <QColor>
#include "WaitingRoom.h"

class JoinRoom : public QMainWindow
{
	Q_OBJECT

public:
	JoinRoom();
	JoinRoom(std::string username, QWidget *parent = nullptr);
	~JoinRoom();

	void paintEvent(QPaintEvent* event) override;

private slots:
	void clickOnInsertButton();
	void clickOnCreateButton();

private:
	Ui::JoinRoomClass ui;
	std::string m_user;

	WaitingRoom m_waiting;
};
