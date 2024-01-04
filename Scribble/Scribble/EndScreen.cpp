#include "EndScreen.h"
#include <QPixmap>

EndScreen::EndScreen()
{
}

EndScreen::EndScreen(std::string username, QWidget *parent)
	: QMainWindow(parent),
	m_user(username)
{
	ui.setupUi(this);

	QPixmap background("");
	background = background.scaled(1280, 720, Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, background);
	setPalette(palette);

	showFullScreen();

}

EndScreen::~EndScreen()
{}
