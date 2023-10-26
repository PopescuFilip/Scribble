#pragma once
#include <cstdint>
#include <vector>
class Score
{
public:
	Score();
	void CalculateScoreGuesser(uint8_t);
	void CalculateScorePainter();
private:
	int16_t m_score;
	static std::vector<int8_t> m_times;
	static const uint8_t BONUS_THRESHHOLD = 30;
	static const uint8_t MAX_ROUND_LENGTH = 60;
	static const uint8_t MAX_POINTS = 100;
	uint8_t ScoreFormula(uint8_t);
};

