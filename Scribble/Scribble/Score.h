#pragma once
#include <cstdint>
#include <vector>
class Score
{
public:
	void CalculateScoreGuesser(uint8_t);
	void CalculateScorePainter(std::vector<Score>);
private:
	int16_t score;
	static const uint8_t BONUS_THRESHHOLD = 30;
	static const uint8_t MAX_ROUND_LENGTH = 60;
	static const uint8_t MAX_POINTS = 100;
	uint8_t ScoreFormula(uint8_t);
};

