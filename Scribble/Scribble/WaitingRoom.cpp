#include "WaitingRoom.h"
#include <QPixmap>

WaitingRoom::WaitingRoom(QWidget *parent)
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

	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(clickOnStartButton()));
}

WaitingRoom::~WaitingRoom()
{}

void WaitingRoom::clickOnStartButton()
{
	close();
	m_scribble.show();
}

void WaitingRoom::paintEvent(QPaintEvent* event)
{
	//ui.pushButton->setStyleSheet("background-color: green; border-radius: 10px;");
	//ui.textEdit->setStyleSheet("background-color: white; border-radius: 10px;");
}
