#include "WaitingRoom.h"

WaitingRoom::WaitingRoom(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

WaitingRoom::~WaitingRoom()
{}

void WaitingRoom::paintEvent()
{
	ui.pushButton->setStyleSheet("background-color: green; border-radius: 10px;");
	ui.textEdit->setStyleSheet("background-color: white; border-radius: 10px;");
	ui.centralWidget->setStyleSheet("background-color: blue;");
}
