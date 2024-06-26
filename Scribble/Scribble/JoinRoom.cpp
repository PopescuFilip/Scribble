#include "JoinRoom.h"
#include <QPixmap>
#include <qmessagebox.h>

JoinRoom::JoinRoom(int username, QWidget* parent)
	: QMainWindow{ parent },
	m_userId{ username }
{
	ui.setupUi(this);

	setAttribute(Qt::WA_DeleteOnClose);

	QPixmap background("Images/JoinRoomBackground.png");
	background = background.scaled(1280, 720, Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, background);
	setPalette(palette);

	setFixedSize(1280, 720);
	setGeometry(140, 70, 2560, 1440);

	connect(ui.insertButton, SIGNAL(clicked()), this, SLOT(clickOnInsertButton()));
	connect(ui.createButton, SIGNAL(clicked()), this, SLOT(clickOnCreateButton()));
	connect(ui.profileButton, SIGNAL(clicked()), this, SLOT(clickOnProfileButton()));
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
	std::string code{ ui.lineEdit->text().toUtf8().constData() };
	cpr::Response response{ JoinRoomRoute(m_userId,code) };

	if (response.status_code != 200)
	{
		ui.lineEdit->clear();
		QMessageBox::warning(this, "Join room", "incorrect code");
		return;
	}

	close();
	WaitingRoom* newWindow = new WaitingRoom{ m_userId, code };
	newWindow->show();
}

void JoinRoom::clickOnCreateButton()
{
	cpr::Response response{ CreateRoom(m_userId) };

	if (response.status_code != 200)
	{
		QMessageBox::critical(this, "Error", "somethins went wrong");
		return;
	}
	
	const auto code{ response.text };

	close();
	WaitingRoom* newWindow = new WaitingRoom{ m_userId, code, true };
	newWindow->show();
}

void JoinRoom::clickOnProfileButton()
{
	Profile* newWindow = new Profile{ m_userId, this };
	newWindow->show();
}
