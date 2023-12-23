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

void Player::SetHasGuessed(bool hasGuessed)
{
	m_hasGuessed = hasGuessed;
}

void Player::SetWordLastGuessed(const std::string& wordLastGuessed)
{
	m_wordLastGuessed = wordLastGuessed;
}
bool Player::GetCanDraw() const
{
	return m_canDraw;
}

Score Player::GetScore() const
{
	return m_score;
}

bool Player::GetHasGuessed() const 
{
	return m_hasGuessed;
}

std::string Player::GetWordLastGuessed() const 
{
	return m_wordLastGuessed;
}

void ScribbleServer::Player::GuessWord(const std::string& word, uint16_t time)
{
	if (m_canDraw) 
	{
		return;
	}

	m_wordLastGuessed = word; 
	m_hasGuessed = true; 
	m_timeGuessedCorrectly = time;
}
