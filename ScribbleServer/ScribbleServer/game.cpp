#include "game.h"
#include <ranges>

using namespace ScribbleServer;

Game::Game(const std::shared_ptr<GameStorage>& db):
    m_db{ db },
    m_roundTimer{ kRoundDuration },
    m_gameState{ GameState::NotStarted }
{}

void Game::AddPlayer(const int userId)
{
    auto sp = m_db.lock();
    User user{ sp->GetUser(userId) };
	m_players.emplace(userId, std::move(Player{ user }));
}

void Game::Run()
{
	for (int i = 0; i < kNoOfRounds; i++)
	{
		RunOneRound();
		//Sleep(kMilisecondBetweenRounds);
		//Reset();
	}
	m_gameState = GameState::Ended;
}

void Game::RunOneRound()
{
	std::ranges::for_each(m_players, [&](const auto& keyValue)
		{
			const auto& [playerId, player] = keyValue;
			RunSubRound(playerId);
			UpdateScores(playerId);
			Sleep(kMilisecondBetweenRounds);
			Reset();

		});
}

void Game::RunSubRound(const int& painterId)
{
	auto sp = m_db.lock();
	m_currentWord = std::move(sp->GetRandomWord());

	Timer startRevealing{ static_cast<uint16_t>(kRoundDuration / 2) };
	Timer revealInterval{ static_cast<uint16_t>(kRoundDuration / m_currentWord.GetNoOfCharacters()) };

	m_gameState = GameState::Running;

	m_roundTimer.Start();
	startRevealing.Start();

	while (!m_roundTimer.ReachedThreshold())
	{
		if (revealInterval.IsActive() && revealInterval.ReachedThreshold())
		{
			m_currentWord.RevealRandomCharacter();
			std::cout << m_currentWord.GetVisibleCharacters() << '\n';
			revealInterval.Start();
		}

		std::cout << m_roundTimer.GetElapsedTime() << "\n";
		//std::this_thread::sleep_for(std::chrono::seconds(1));
		Sleep(1000);

		if (!startRevealing.IsActive())
			continue;
		if (!startRevealing.ReachedThreshold())
			continue;

		revealInterval.Start();
		startRevealing.Stop();
	}
	m_roundTimer.Stop();
	revealInterval.Stop();

	m_gameState = GameState::BetweenRounds;
}

void Game::UpdateScores(const int& painterId)
{
	std::vector<uint16_t> times;

	std::ranges::for_each(m_players, [&painterId, &times](auto& keyValue) 
		{
			auto& [playerId, player] = keyValue;
			if (playerId == painterId)
				return;

			if (!player.HasGuessedCorrectly())
			{
				times.emplace_back(kRoundDuration);
				player.SetScore(kRoundDuration);
				return;
			}

			const uint16_t& timeGuessed{ player.GetTimeGuessed() };
			times.emplace_back(timeGuessed);
			player.SetScore(timeGuessed);
		});

	m_players.at(painterId).SetScore(times);
}

void Game::Reset()
{
}

uint16_t Game::GetTime() const
{
    if (m_gameState == GameState::Running && m_roundTimer.IsActive()) 
    {
        return m_roundTimer.GetElapsedTime();
    }
    else
    {
        return 0;
    }
}

GameState Game::GetGameState() const
{
    return m_gameState;
}
