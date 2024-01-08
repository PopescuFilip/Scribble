#include "WaitingRoom.h"
#include <QPixmap>

WaitingRoom::WaitingRoom(std::string username, std::string code, QWidget* parent)
	: QMainWindow(parent),
	m_user(username),
	m_roomCode(code)
{
	ui.setupUi(this);

	QPixmap background("Images/Background.png");
	background = background.scaled(1280, 720, Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, background);
	setPalette(palette);

	showFullScreen();

	connect(ui.startButton, SIGNAL(clicked()), this, SLOT(clickOnStartButton()));
}

WaitingRoom::~WaitingRoom()
{
	close();
    Scribble* newWindow = new Scribble(m_user);
	newWindow->show();
}

void WaitingRoom::clickOnStartButton()
{
	close();
	Scribble* newWindow = new Scribble(m_user);
	newWindow->show();
}

void WaitingRoom::paintEvent(QPaintEvent* event)
{
	//ui.pushButton->setStyleSheet("background-color: green; border-radius: 10px;");
	//ui.textEdit->setStyleSheet("background-color: white; border-radius: 10px;");
}
