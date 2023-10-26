#include "Score.h"

Score::Score(): m_score(0)
{}

void Score::CalculateScoreGuesser(uint8_t time)
{
	Score::m_times.push_back(time);
	if (time <= Score::BONUS_THRESHHOLD)
	{
		m_score += Score::MAX_POINTS;
		return;
	}
	if (time == Score::MAX_ROUND_LENGTH)
	{
		m_score -= Score::MAX_POINTS / 2;
		return;
	}
	uint8_t scoreGained = ScoreFormula(time);
	m_score += scoreGained;
}

void Score::CalculateScorePainter()
{
	bool atLeastOneGuessed = false;
	int16_t averageTime = 0;
	for (const int8_t& time : Score::m_times)
	{
		if (time != Score::MAX_ROUND_LENGTH)
			atLeastOneGuessed = true;
		averageTime += time;
	}
	averageTime /= Score::m_times.size();
	Score::m_times.clear();
	if (atLeastOneGuessed)
	{
		uint8_t scoreGained = ScoreFormula(averageTime);
		m_score += scoreGained;
		return;
	}
	m_score -= Score::MAX_POINTS;
}

uint8_t Score::ScoreFormula(uint8_t duration)
{
	return (Score::MAX_ROUND_LENGTH - duration) * Score::MAX_POINTS * 2 / Score::MAX_ROUND_LENGTH;
}
