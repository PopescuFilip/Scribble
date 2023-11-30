import player;
import score;
import user;

using namespace ScribbleServer;

Player::Player() :
	m_canDraw{ false }, 
	m_guessedCorrectly{ false }, 
	User{}
{
};

Player::Player(const std::string& username, const std::string& password)
	: m_canDraw{ false }, 
	m_guessedCorrectly{ false }, 
	User{ username, password }
{
}

bool Player::GetCanDraw()
{
	return m_canDraw;
}

Score Player::GetScore()
{
	return m_score;
}

bool Player::GetGuessedCorrectly()
{
	return m_guessedCorrectly;
}

void Player::SetCanDraw(bool canDraw)
{
	m_canDraw = canDraw;
}

void Player::SetScore(uint16_t time)
{
	m_score.CalculateScoreGuesser(time);
}

void Player::SetScore(const std::vector<uint16_t>& times)
{
	m_score.CalculateScorePainter(times);
}

void Player::SetGuessedCorrectly(bool guessedCorrectly)
{
	m_guessedCorrectly = guessedCorrectly;
}
