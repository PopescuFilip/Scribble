#include "JoinRoom.h"
#include <QPixmap>

JoinRoom::JoinRoom(std::string username, QWidget* parent)
	: QMainWindow(parent),
	  m_user(username)
{
	ui.setupUi(this);

	QPixmap background("Images/Background.png");
	background = background.scaled(1280, 720, Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, background);
	setPalette(palette);

	setFixedSize(1280, 720);
	setGeometry(140, 70, 2560, 1440);

	QString buttonStyle = "QPushButton {"
		"background-color: #4CAF50;"
		"border-width: 2px;"
		"border - style: dashed;"
		"border - color: white;"
		"color: purple;"
		"padding: 5px 5px;"
		"text-align: center;"
		"text-decoration: none;"
		"font-size: 12px;"
		"border-radius: 1px;"
		"font-weight: bold;"
		"}"
		"QPushButton:hover {"
		"background-color: #45a049;"
		"}";

	ui.insertButton->setStyleSheet(buttonStyle);
	ui.createButton->setStyleSheet(buttonStyle);

	connect(ui.insertButton, SIGNAL(clicked()), this, SLOT(clickOnInsertButton()));
	connect(ui.createButton, SIGNAL(clicked()), this, SLOT(clickOnCreateButton()));
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
	WaitingRoom* newWindow = new WaitingRoom(m_user, " ");
	newWindow->show();
}

void JoinRoom::clickOnCreateButton()
{
	close();
	WaitingRoom* newWindow = new WaitingRoom(m_user, " ");
	newWindow->show();
}
