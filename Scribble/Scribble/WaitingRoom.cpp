#include "WaitingRoom.h"
#include <QPixmap>
#include "Scribble.h"

WaitingRoom::WaitingRoom(QWidget *parent)
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

	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(clickOnStartButton()));
}

WaitingRoom::~WaitingRoom()
{}

void WaitingRoom::clickOnStartButton()
{
	close();
	Scribble* s = new Scribble(this);
	s->show();
}

void WaitingRoom::paintEvent(QPaintEvent* event)
{
	ui.pushButton->setStyleSheet("background-color: green; border-radius: 10px;");
	ui.textEdit->setStyleSheet("background-color: white; border-radius: 10px;");
	ui.centralWidget->setStyleSheet("background-color: blue;");
}
