#pragma once
#include "timer.h"
#include "gameState.h"
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
		Game(const std::shared_ptr<GameStorage>& db);

		uint16_t GetTime()const;
		GameState GetGameState()const;

	    void AddPlayer(const int userId);
		void Run();

		static const std::string GetStringFromGameState(const GameState& gameState);
	
	private:
		void RunOneRound();
		void RunSubRound(const int& painterId);
		void UpdateScores(const int& painterId);
		void Reset();

	private:
		std::weak_ptr<GameStorage> m_db;
		GameState m_gameState;
		std::unordered_map<int, Player> m_players;
		std::deque<Line> m_drawing;
		Word m_currentWord;

		Timer m_roundTimer;

		static const uint16_t kNoOfRounds = 4;
		static const uint16_t kRoundDuration = 10;

	};
}
