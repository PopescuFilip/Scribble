#include "EndScreen.h"
#include <QPixmap>

EndScreen::EndScreen(const std::string& roomCode, QWidget* parent)
	: QMainWindow(parent),
	m_roomCode{ roomCode }
{
	ui.setupUi(this);

	QPixmap background("Images/EndScreenBackground.png");
	background = background.scaled(1280, 720, Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, background);
	setPalette(palette);

	setFixedSize(1280, 720);
	setGeometry(140, 70, 2560, 1440);

	ShowRanking();
}


EndScreen::~EndScreen()
{}

void EndScreen::ShowRanking()
{
	cpr::Response response{ GetPlayers(m_roomCode) };
	if (response.status_code != 200)
	{
		QMessageBox::critical(this, "Error", "something went wrong");
		return;
	}

	std::vector<std::pair<std::string, int>> ranking;
	auto players = crow::json::load(response.text);
	for (const auto& player : players)
	{
		ranking.push_back({ player["name"].s(), player["score"].i() });
	}

	std::ranges::sort(ranking, [](const auto& a, const auto& b) { return a.second > b.second; });
	std::stringstream ss;
	std::ranges::for_each(ranking, [&ss](const auto& pair)
		{
			const auto& [name, score] = pair;
			ss << name << " " << std::to_string(score) << "\n";
		});

	ui.textEdit->setPlainText(QString::fromUtf8(ss.str().c_str()));
	ui.textEdit->setReadOnly(true);
}
