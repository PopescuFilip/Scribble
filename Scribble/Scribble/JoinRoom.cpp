#include "JoinRoom.h"
#include <QPixmap>

JoinRoom::JoinRoom(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QPixmap background("");
	background = background.scaled(1280, 1440, Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, background);
	setPalette(palette);
	setFixedSize(1280, 720);
	setGeometry(140, 70, 2560, 1440);
}

JoinRoom::~JoinRoom()
{}

void JoinRoom::paintEvent(QPaintEvent* event)
{
	ui.pushButton_2->setStyleSheet("background-color: SkyBlue; border-radius: 10px;");
	ui.pushButton->setStyleSheet("background-color: Green; border-radius: 10px;");
	ui.groupBox->setStyleSheet("background-color: blue; border-radius: 10px;");
	ui.centralWidget->setStyleSheet("background-color: DodgerBlue;");
}
