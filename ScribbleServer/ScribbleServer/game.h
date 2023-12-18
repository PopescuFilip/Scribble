#pragma once
#include <unordered_map>
#include "gameDatabase.h"
import player;
import word;

namespace ScribbleServer
{
	class Game
	{
	public:

	public:
		using Point = std::pair<uint16_t, uint16_t>;
		using Line = std::pair<Point, Point>;

	private:
		//GameStorage& m_db;
		std::unordered_map<int, Player> m_players;
		std::vector<Line> m_drawing;
		Word m_currentWord;
	};
}

