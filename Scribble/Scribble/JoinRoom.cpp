#include "JoinRoom.h"
#include <QPixmap>

JoinRoom::JoinRoom(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QPixmap background("Images/Background.png");
	background = background.scaled(1280, 720, Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, background);
	setPalette(palette);
	setFixedSize(1280, 720);
	setGeometry(140, 70, 2560, 1440);

	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(clickOnInsertButton()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(clickOnCreateButton()));
}

JoinRoom::~JoinRoom()
{}

void JoinRoom::paintEvent(QPaintEvent* event)
{
	//ui.pushButton_2->setStyleSheet("background-color: SkyBlue; border-radius: 10px;");
	//ui.pushButton->setStyleSheet("background-color: Green; border-radius: 10px;");
}

void JoinRoom::clickOnInsertButton()
{
	close();
	m_waiting.show();
}

void JoinRoom::clickOnCreateButton()
{
	close();
	m_waiting.show();
}
