#pragma once
#include <unordered_map>
#include "gameDatabase.h"
import <chrono>;
import player;
import word;
import timer;


namespace ScribbleServer
{
	class Game
	{
	public:
		enum class GameState
		{
			NotStarted,
			BetweenRounds,
			Running,
			Ended
		};
	public:
		using Point = std::pair<uint16_t, uint16_t>;
		using Line = std::pair<Point, Point>;

	private:
		//GameStorage& m_db;
		std::unordered_map<int, Player> m_players;
		std::vector<Line> m_drawing;
		Word m_currentWord;

		Timer roundTimer;
		Timer startRevealTimer;
		Timer intervalTimer;
	};
}

