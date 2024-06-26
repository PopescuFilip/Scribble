#include "WaitingRoom.h"
#include <QPixmap>
#include <qmessagebox.h>

WaitingRoom::WaitingRoom(int username, std::string code, bool isOwner, QWidget* parent)
	: QMainWindow{ parent },
	m_isOwner{ isOwner },
	m_userId{ username },
	m_roomCode{ code }
{
	ui.setupUi(this);
	ui.textEdit->setPlainText(QString::fromUtf8(m_roomCode.c_str()));
	ui.textEdit->setReadOnly(true);
	setAttribute(Qt::WA_DeleteOnClose);

	QPixmap background("Images/WaitingRoomBackground.png");
	background = background.scaled(1280, 720, Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, background);
	setPalette(palette);

	setFixedSize(1280, 720);
	setGeometry(140, 70, 2560, 1440);

	if (isOwner)
		connect(ui.startButton, SIGNAL(clicked()), this, SLOT(clickOnStartButton()));
	
	QObject::connect(&m_refreshTimer, &QTimer::timeout, this, &WaitingRoom::checkGameState);
	m_refreshTimer.setInterval(5000);
	m_refreshTimer.start();

	ShowPlayers();
}

WaitingRoom::~WaitingRoom()
{
	
}

void WaitingRoom::clickOnStartButton()
{
	cpr::Response response{ Start(m_userId,m_roomCode) };

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

	m_refreshTimer.stop();
	close();
	Scribble* newWindow = new Scribble{ m_userId, m_roomCode };
	newWindow->show();
}

void WaitingRoom::paintEvent(QPaintEvent* event)
{
	//ui.plainTextEdit->setPlainText(QString::fromStdString(m_roomCode));
	//ui.pushButton->setStyleSheet("background-color: green; border-radius: 10px;");
	//ui.textEdit->setStyleSheet("background-color: white; border-radius: 10px;");
}

void WaitingRoom::ShowPlayers()
{
	cpr::Response response{ GetPlayers(m_roomCode) };

	if (response.status_code != 200)
	{
		QMessageBox::critical(this, "Error", "something went wrong");
		return;
	}

	std::stringstream ss;
	auto players = crow::json::load(response.text);
	for (const auto& player : players)
	{
		ss << player["name"].s() << "\n";
	}
	ui.textEditPlayers->setReadOnly(false);
	ui.textEditPlayers->setPlainText(QString::fromUtf8(ss.str().c_str()));
	ui.textEditPlayers->setReadOnly(true);
}

void WaitingRoom::CheckState()
{
	cpr::Response response{ GetGameState(m_roomCode) };

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
		Scribble* newWindow = new Scribble(m_userId, m_roomCode);
		newWindow->show();
		return;
	}
	m_refreshTimer.start();
}

void WaitingRoom::checkGameState()
{
	m_refreshTimer.stop();

	ShowPlayers();

	if (m_isOwner)
	{
		m_refreshTimer.start();
		return;
	}

	CheckState();
}
