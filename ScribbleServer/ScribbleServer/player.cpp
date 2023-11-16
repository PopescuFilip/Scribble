import player;
import score;
import user;
using ScribbleServer::Player;
using ScribbleServer::Score;

ScribbleServer::Player::Player() :m_canDraw{ false }, m_guessedCorrectly{ false }, User()
{
};

ScribbleServer::Player::Player(const std::string& username, const std::string& password)
	: m_canDraw{ false }, m_guessedCorrectly{ false }, User{ username, password }
{
}

std::string ScribbleServer::Player::GetWordLastGuessed()
{
	return m_wordLastGuessed;
}

bool ScribbleServer::Player::GetCanDraw()
{
	return m_canDraw;
}

Score ScribbleServer::Player::GetScore()
{
	return m_score;
}

bool ScribbleServer::Player::GetGuessedCorrectly()
{
	return m_guessedCorrectly;
}

void ScribbleServer::Player::SetWordLastGuessed(const std::string& wordLastGuessed)
{
	m_wordLastGuessed = wordLastGuessed;
}

void ScribbleServer::Player::SetCanDraw(bool canDraw)
{
	m_canDraw = canDraw;
}

void ScribbleServer::Player::SetScore(const Score& score)
{
	m_score = score;
}

void ScribbleServer::Player::SetGuessedCorrectly(bool guessedCorrectly)
{
	m_guessedCorrectly = guessedCorrectly;
}
