#pragma once
#include<iostream>
#include<vector>

import round;
import player;

namespace ScribbleServer
{

	class GameRoom
	{
	public:
		GameRoom();
		using Point = std::pair<uint16_t, uint16_t>;
		using Line = std::pair<Point, Point>;

	private:
		std::vector<Player> m_players;
		std::vector<Line> m_drawing;
		Round m_currentRound;
	};

}