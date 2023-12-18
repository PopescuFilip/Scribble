import score;
import<vector>;
using ScribbleServer::Score;

Score::Score() :
	m_scoreId{ -1 },
	m_userId{ -1 },
	m_score{ 0 }
{}

int16_t Score::GetScore() const
{
	return m_score;
}


int Score::GetScoreId() const
{
	return m_scoreId;
}

int Score::GetUserId() const
{
	return m_userId;
}

void Score::SetScore(const int16_t& score)
{
	m_score = score;
}

void Score::SetScoreId(const int& scoreId)
{
	m_scoreId = scoreId;
}

void Score::SetUserId(const int& usernameId)
{
	m_userId = usernameId;
}


void Score::CalculateScoreGuesser(uint16_t time)
{
	if (time <= Score::kBONUS_THRESHHOLD)
	{
		m_score += Score::kMAX_POINTS;
		return;
	}
	if (time == Score::kMAX_ROUND_LENGTH)
	{
		m_score -= Score::kMAX_POINTS / 2;
		return;
	}
	uint16_t scoreGained = ScoreFormula(time);
	m_score += scoreGained;
}

void Score::CalculateScorePainter(const std::vector<uint16_t>& times)
{
	bool atLeastOneGuessed = false;
	int16_t averageTime = 0;
	for (const int16_t& time : times)
	{
		if (time != Score::kMAX_ROUND_LENGTH)
			atLeastOneGuessed = true;
		averageTime += time;
	}
	averageTime /= times.size();
	if (atLeastOneGuessed)
	{
		uint16_t scoreGained = ScoreFormula(averageTime);
		m_score += scoreGained;
		return;
	}
	m_score -= Score::kMAX_POINTS;
}

uint16_t Score::ScoreFormula(uint16_t duration)
{
	return (Score::kMAX_ROUND_LENGTH - duration) * Score::kMAX_POINTS * 2 / Score::kMAX_ROUND_LENGTH;
}
