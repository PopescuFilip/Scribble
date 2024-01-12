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
		Game(const std::shared_ptr<GameStorage>& db, int ownerId);

		uint16_t GetTime()const;
		GameState GetGameState()const;
		int GetOwnerId() const;

		std::deque<Line> GetDrawing()const;
		std::deque<Score> GetScores() const;
		int GetPainterId() const;
		std::deque<Player> GetPlayers() const;

		void SetDrawingFromString(const std::string& string);
	    void AddPlayer(const int userId);
		void Run();
		void GuessWord(int playerId, const std::string& word);
	
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

		int m_painterId;
		const int m_ownerId;

		Timer m_roundTimer;

		static const uint16_t kNoOfRounds = 4;
		static const uint16_t kRoundDuration = 60;
		static const uint16_t kMilisecondBetweenRounds = 5000;

	};
}
