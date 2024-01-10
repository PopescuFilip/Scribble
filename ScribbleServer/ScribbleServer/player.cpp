import player;
import score;
import user;

using namespace ScribbleServer;

Player::Player(const User& user) :
	User{ user },
	m_canDraw{ false },
	m_guessedCorrectly{ false },
	m_hasGuessed{ false },
	m_score{ user.GetUserId() }
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

bool Player::HasGuessedCorrectly() const
{
	return m_guessedCorrectly;
}

bool Player::HasGuessed() const
{
	return m_hasGuessed;
}

std::string Player::GetWordLastGuessed() const
{
	return m_wordLastGuessed;
}

uint16_t Player::GetTimeGuessed() const
{
	return m_timeGuessed;
}

void Player::GuessWord(const std::string& word, uint16_t time)
{
	if (m_canDraw or m_guessedCorrectly)
	{
		return;
	}

	m_wordLastGuessed = word;
	m_hasGuessed = true;
	m_timeGuessed = time;
}

void Player::Reset()
{
	m_canDraw = false;
	m_guessedCorrectly = false;
	m_hasGuessed = false;
}
