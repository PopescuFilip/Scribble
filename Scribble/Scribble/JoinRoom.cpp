#include "JoinRoom.h"

JoinRoom::JoinRoom(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

JoinRoom::~JoinRoom()
{}

void JoinRoom::paintEvent()
{
	ui.pushButton_2->setStyleSheet("background-color: SkyBlue; border-radius: 10px;");
	ui.pushButton->setStyleSheet("background-color: Green; border-radius: 10px;");
	ui.groupBox->setStyleSheet("background-color: blue; border-radius: 10px;");
	ui.centralWidget->setStyleSheet("background-color: DodgerBlue;");
}
