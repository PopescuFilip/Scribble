#pragma once
#include <unordered_map>
#include "gameDatabase.h"
import player;
import word;
import timer;

namespace ScribbleServer
{
	class Game
	{
	public:
		Game(GameStorage& db);

	    void AddPlayer(const std::string& username);
		void Run();
		void RunOneRound(const int& painterId);
		uint16_t GetTime()const;
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
		GameStorage& m_db;
		std::unordered_map<int, Player> m_players;
		std::vector<Line> m_drawing;
		Word m_currentWord;

		Timer roundTimer;
		Timer startRevealTimer;
		Timer intervalTimer;

		static const uint16_t kNoOfRounds = 4;
		static const uint16_t kRoundDuration = 60;

		GameState m_gameState;
	};
}
