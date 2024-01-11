#include "WaitingRoom.h"
#include <QPixmap>
#include <qmessagebox.h>

WaitingRoom::WaitingRoom(int username, std::string code, QWidget* parent)
	: QMainWindow(parent),
	m_userId(username),
	m_roomCode(code)
{
	ui.setupUi(this);
	ui.textEdit->setText(QString::fromStdString(code));

	QPixmap background("Images/Background.png");
	background = background.scaled(1280, 720, Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, background);
	setPalette(palette);

	setFixedSize(1280, 720);
	setGeometry(140, 70, 2560, 1440);

	connect(ui.startButton, SIGNAL(clicked()), this, SLOT(clickOnStartButton()));
}

WaitingRoom::~WaitingRoom()
{
	
}

void WaitingRoom::clickOnStartButton()
{
	cpr::Response response = cpr::Get(
		cpr::Url{ "http://localhost:18080/start" },
		cpr::Parameters{
		{ "id" , std::to_string(m_userId) },
		{ "code", m_roomCode }
		}
	);

	if (response.status_code == 203)
	{
		QMessageBox::warning(this, "Start", "you are not the owner of game room");
		return;
	}

	if (response.status_code != 200)
	{
		QMessageBox::critical(this, "Error", "something went wrong");
		return;
	}

	close();
	Scribble* newWindow = new Scribble(m_userId);
	newWindow->show();
}

void WaitingRoom::paintEvent(QPaintEvent* event)
{
	//ui.pushButton->setStyleSheet("background-color: green; border-radius: 10px;");
	//ui.textEdit->setStyleSheet("background-color: white; border-radius: 10px;");
}
