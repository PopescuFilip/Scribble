#include "Profile.h"
#include <QPixmap>
#include "Routes.h"

Profile::Profile(int username, QWidget *parent)
	: QMainWindow(parent),
	m_userId(username)
{
	ui.setupUi(this);

	QPixmap background("Images/PlayerProfileBackground.png");
	background = background.scaled(1280, 720, Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, background);
	setPalette(palette);

	setFixedSize(1280, 720);
	setGeometry(140, 70, 2560, 1440);

	ShowScores();
}

Profile::~Profile()
{}

void Profile::ShowScores()
{
	cpr::Response response{ GetProfile(m_userId) };
	if (response.status_code != 200)
	{
		QMessageBox::warning(this, "Error", "something went wrong");
		return;
	}

	auto scoresJson{ crow::json::load(response.text) };
	std::vector<int> scores;
	for (const auto& score : scoresJson)
	{
		scores.push_back(score["score"].i());
	}
	int sum{ std::accumulate(scores.begin(), scores.end(), 0) };
	int average{ static_cast<int>(sum / scores.size()) };

	std::stringstream ss;
	std::ranges::for_each(scores, [&ss](const auto& score) 
		{
			ss << score << "\n";
		});

	ui.textEditAverage->setPlainText(QString::fromUtf8(std::to_string(average).c_str()));
	ui.textEditAverage->setReadOnly(true);
	ui.textEdit->setPlainText(QString::fromUtf8(ss.str().c_str()));
	ui.textEdit->setReadOnly(true);
}
