#include "Profile.h"
#include <QPixmap>
Profile::Profile()
{
}
Profile::Profile(std::string username, QWidget *parent)
	: QMainWindow(parent),
	m_user(username)
{
	ui.setupUi(this);

	QPixmap background("");
	background = background.scaled(1280, 1440, Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, background);
	setPalette(palette);

	showFullScreen();
}

Profile::~Profile()
{}

void Profile::clickedOnButton(std::string username, std::string code)
{
	WaitingRoom* newWindow = new WaitingRoom(username, code);
	newWindow->show();
}