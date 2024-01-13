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
		Game(std::shared_ptr<GameStorage> db, int ownerId);

		uint16_t GetTime()const;
		GameState GetGameState()const;
		int GetOwnerId() const;

		std::string GetDrawing()const;
		std::deque<Score> GetScores() const;
		int GetPainterId() const;
		std::string GetWord(const int& playerId) const;
		std::deque<Player> GetPlayers() const;

		void SetDrawing(const std::string& string);
	    void AddPlayer(const int userId);
		void Run();
		bool GuessWord(int playerId, const std::string& word);
	
	private:
		bool AllHaveGuessed();
		void RunOneRound();
		void RunSubRound();
		void PreSubRoundSetup(const int& painterId);
		void PostSubRoundSetup();
		void UpdateScores(const int& painterId);
		void Reset();

		void PutScoresToDb();

	private:
		std::shared_ptr<GameStorage> m_db;
		GameState m_gameState;
		std::unordered_map<int, Player> m_players;
		std::string m_drawingString;
		Word m_currentWord;

		int m_painterId;
		const int m_ownerId;

		Timer m_roundTimer;

		static const uint16_t kNoOfRounds = 1;
		static const uint16_t kRoundDuration = 60;
		static const uint16_t kMilisecondBetweenRounds = 5000;

	};
}
