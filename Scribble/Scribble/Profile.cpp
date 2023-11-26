#include "Profile.h"
#include <QPixmap>
Profile::Profile(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QPixmap background("");
	background = background.scaled(1280, 1440, Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, background);
	setPalette(palette);
	setFixedSize(1280, 720);
	setGeometry(140, 70, 2560, 1440);
}

Profile::~Profile()
{}
