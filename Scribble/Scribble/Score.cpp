#include "Score.h"

void Score::CalculateScoreGuesser(uint8_t duration)
{
	if (duration <= Score::BONUS_THRESHHOLD)
	{
		score += Score::MAX_POINTS;
		return;
	}
	if (duration == Score::MAX_ROUND_LENGTH)
	{
		score -= Score::MAX_POINTS;
		return;
	}
	score += ScoreFormula(duration);
}

uint8_t Score::ScoreFormula(uint8_t duration)
{
	return (Score::MAX_ROUND_LENGTH - duration) * 100 / 30;
}
