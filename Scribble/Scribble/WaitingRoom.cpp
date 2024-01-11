#include "WaitingRoom.h"
#include <QPixmap>
#include <qmessagebox.h>

WaitingRoom::WaitingRoom(int username, std::string code, bool isOwner, QWidget* parent)
	: QMainWindow(parent),
	m_isOwner{ isOwner },
	m_userId(username),
	m_roomCode(code)
{
	ui.setupUi(this);
	ui.textEdit->setPlainText(QString::fromUtf8(m_roomCode.c_str()));
	ui.textEdit->setReadOnly(true);

	QPixmap background("Images/Background.png");
	background = background.scaled(1280, 720, Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, background);
	setPalette(palette);

	setFixedSize(1280, 720);
	setGeometry(140, 70, 2560, 1440);

	if (isOwner)
		connect(ui.startButton, SIGNAL(clicked()), this, SLOT(clickOnStartButton()));
	else
	{
		m_refreshTimer.setInterval(2000);
		m_refreshTimer.start();

		QObject::connect(&m_refreshTimer, &QTimer::timeout, this, &WaitingRoom::checkGameState);
	}
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
	//ui.plainTextEdit->setPlainText(QString::fromStdString(m_roomCode));
	//ui.pushButton->setStyleSheet("background-color: green; border-radius: 10px;");
	//ui.textEdit->setStyleSheet("background-color: white; border-radius: 10px;");
}

void WaitingRoom::checkGameState()
{
	cpr::Response response = cpr::Get(
		cpr::Url{ "http://localhost:18080/gamestate" },
		cpr::Parameters{
		{ "code", m_roomCode }
		}
	);

	if (response.status_code == 404)
	{
		QMessageBox::warning(this, "Game room", "invalid code");
		return;
	}

	if (response.status_code != 200)
	{
		QMessageBox::critical(this, "Error", "something went wrong");
		return;
	}

	const auto stringState{ response.text };

	if (GetGameStateFromString(stringState) == GameState::Running)
	{
		m_refreshTimer.stop();
		close();
		Scribble* newWindow = new Scribble(m_userId);
		newWindow->show();
		return;
	}

	//m_refreshTimer.start();
}
