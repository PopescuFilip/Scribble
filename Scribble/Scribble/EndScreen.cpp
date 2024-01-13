#include "EndScreen.h"
#include <QPixmap>

EndScreen::EndScreen(int username, QWidget *parent)
	: QMainWindow(parent),
	m_userId(username)
{
	ui.setupUi(this);

	QPixmap background("Images/EndScreenBackground.png");
	background = background.scaled(1280, 720, Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, background);
	setPalette(palette);

	setFixedSize(1280, 720);
	setGeometry(140, 70, 2560, 1440);

}

EndScreen::~EndScreen()
{}
