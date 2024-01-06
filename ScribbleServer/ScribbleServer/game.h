#pragma once
#include "timer.h"
#include <unordered_map>
#include "gameDatabase.h"
import player;
import word;
//import timer;

namespace ScribbleServer
{
	class Game
	{
	public:
		using Point = std::pair<uint16_t, uint16_t>;
		using Line = std::pair<Point, Point>;
	public:
		enum class GameState
		{
			NotStarted,
			BetweenRounds,
			Running,
			Ended
		};
	public:
		Game(const std::shared_ptr<GameStorage>& db);

		uint16_t GetTime()const;
		GameState GetGameState()const;

	    void AddPlayer(const int userId);
		void Run();
	
	private:
		void RunOneRound(const int& painterId);
		void UpdateScores(const int& painterId);
		void Reset();

	private:
		std::weak_ptr<GameStorage> m_db;
		GameState m_gameState;
		std::unordered_map<int, Player> m_players;
		std::vector<Line> m_drawing;
		Word m_currentWord;

		Timer m_roundTimer;
		//Timer startRevealTimer;
		//Timer intervalTimer;

		static const uint16_t kNoOfRounds = 4;
		static const uint16_t kRoundDuration = 60;

	};
}
