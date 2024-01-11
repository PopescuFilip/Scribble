#include "JoinRoom.h"
#include <QPixmap>
#include <qmessagebox.h>

JoinRoom::JoinRoom(int username, QWidget* parent)
	: QMainWindow(parent),
	  m_userId(username)
{
	ui.setupUi(this);

	QPixmap background("Images/Background.png");
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
	close();
	WaitingRoom* newWindow = new WaitingRoom(m_userId, " ");
	newWindow->show();
}

void JoinRoom::clickOnCreateButton()
{
	cpr::Response response = cpr::Get(
		cpr::Url{ "http://localhost:18080/createroom" },
		cpr::Parameters{
			{ "id" , std::to_string(m_userId) }
		}
	);
	if (response.status_code != 200)
	{
		QMessageBox::warning(this, "Create room", "somethin went wrong");
		return;
	}
	
	const auto code{ response.text };

	close();
	WaitingRoom* newWindow = new WaitingRoom(m_userId, code);
	newWindow->show();
}

void JoinRoom::clickOnProfileButton()
{
	Profile* newWindow = new Profile(m_userId, this);
	newWindow->show();
}
