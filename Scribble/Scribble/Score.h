#pragma once
#include <chrono>
#include <vector>
class Score
{
public:
	float CalculateScoreGuesser(std::chrono::seconds);
	float CalculateScorePainter(std::vector<Score>);
private:
	int score;
};

