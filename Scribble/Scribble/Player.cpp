import player;
import score;
import user;
using Scribble::Player;
using Scribble::Score;

Scribble::Player::Player():m_canDraw(false), m_guessedCorrectly(false), User()
{
};

Scribble::Player::Player(const std::string& username, const std::string& password)
	: m_canDraw(false),m_guessedCorrectly(false), User(username, password)
{
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

bool Scribble::Player::GetGuessedCorrectly()
{
	return m_guessedCorrectly;
}

void Scribble::Player::SetWordLastGuessed(const std::string& wordLastGuessed)
{
	m_wordLastGuessed = wordLastGuessed;
}

void Scribble::Player::SetCanDraw(bool canDraw)
{
	m_canDraw = canDraw;
}

void Scribble::Player::SetScore(const Score& score)
{
	m_score = score;
}

void Scribble::Player::SetGuessedCorrectly(bool guessedCorrectly)
{
	m_guessedCorrectly = guessedCorrectly;
}
