import player;
import score;
import user;

using namespace ScribbleServer;

Player::Player(const User& user) :
	User{ user },
	m_guessedCorrectly{ false },
	m_score{ std::move(user.GetUserId()) }
{
}

void Player::SetScore(uint16_t time)
{
	m_score.CalculateScoreGuesser(time);
}

void Player::SetScore(const std::vector<uint16_t>& times)
{
	m_score.CalculateScorePainter(times);
}

Score Player::GetScore() const
{
	return m_score;
}

bool Player::HasGuessedCorrectly() const
{
	return m_guessedCorrectly;
}

uint16_t Player::GetTimeGuessed() const
{
	return m_timeGuessed;
}

void Player::GuessWord(uint16_t time)
{
	m_guessedCorrectly = true;
	m_timeGuessed = time;
}

void Player::Reset() 
{
	m_guessedCorrectly = false;
}
