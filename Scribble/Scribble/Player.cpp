import player;
import "Score.h";
using Scribble::Player;

Scribble::Player::Player()
{
};

Scribble::Player::Player(const std::string& username, const std::string& wordLastGuessed, bool canDraw, const Score& score)
	:m_username(username), m_wordLastGuessed(wordLastGuessed), m_canDraw(canDraw), m_score(score)
{
}

std::string Scribble::Player::GetUsername()
{
	return m_username;
}

std::string Scribble::Player::GetWordLastGuessed()
{
	return m_wordLastGuessed;
}

bool Scribble::Player::GetCanDraw()
{
	return m_canDraw;
}

Score Scribble::Player::GetScore()
{
	return m_score;
}





