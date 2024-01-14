#include "game.h"
#include <ranges>

using namespace ScribbleServer;

Game::Game(std::shared_ptr<GameStorage> db, int ownerId) :
	m_db{ db },
	m_roundTimer{ kRoundDuration },
	m_gameState{ GameState::NotStarted },
	m_ownerId{ ownerId }
{}

void Game::SetDrawing(const std::string& string)
{
	m_drawingString = string;
}

void Game::AddPlayer(const int userId)
{
	User user{ m_db->GetUser(userId) };
	m_players.emplace(userId, std::move(Player{ user }));
}

void Game::Run()
{
	for (int i = 0; i < kNoOfRounds; i++)
	{
		Sleep(kMilisecondBetweenRounds);
		RunOneRound();
	}
	m_gameState = GameState::Ended;
	PutScoresToDb();
}

bool Game::GuessWord(int playerId, const std::string& word)
{
	if (playerId == m_painterId)
		return false;

	if (m_gameState != GameState::Running)
		return false;

	uint16_t time{ std::move(GetTime()) };
	if (m_currentWord != word)
		return false;

	m_players.at(playerId).GuessWord(time);
	return true;
}

bool Game::AllHaveGuessed()
{
	for (auto& keyValue : m_players)
	{
		auto& [playerId, player] = keyValue;
		if (playerId == m_painterId)
			continue;
		if (player.HasGuessedCorrectly())
			continue;
		return false;
	}
	return true;
}

void Game::RunOneRound()
{
	std::ranges::for_each(m_players, [&](const auto& keyValue)
		{
			const auto& [playerId, player] = keyValue;
			PreSubRoundSetup(playerId);
			RunSubRound();
			PostSubRoundSetup();
			Sleep(kMilisecondBetweenRounds);

		});
}

void Game::RunSubRound()
{
	Timer startRevealing{ static_cast<uint16_t>(kRoundDuration / 2) };
	Timer revealInterval{ static_cast<uint16_t>(kRoundDuration / m_currentWord.GetNoOfCharacters()) };

	m_roundTimer.Start();
	startRevealing.Start();

	while (!m_roundTimer.ReachedThreshold())
	{
		if (revealInterval.IsActive() && revealInterval.ReachedThreshold())
		{
			m_currentWord.RevealRandomCharacter();
			//std::cout << m_currentWord.GetVisibleCharacters() << '\n';
			revealInterval.Start();
		}

		std::cout << m_roundTimer.GetElapsedTime() << "\n";
		if (AllHaveGuessed())
			return;
		Sleep(500);

		if (!startRevealing.IsActive())
			continue;
		if (!startRevealing.ReachedThreshold())
			continue;

		revealInterval.Start();
		startRevealing.Stop();
	}
	m_roundTimer.Stop();
	revealInterval.Stop();
}

void Game::PreSubRoundSetup(const int& painterId)
{
	m_currentWord = std::move(m_db->GetRandomWord());
	m_painterId = painterId;
	m_gameState = GameState::Running;
}

void Game::PostSubRoundSetup()
{
	m_gameState = GameState::BetweenRounds;
	UpdateScores(m_painterId);
	Reset();
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
	std::ranges::for_each(m_players, [&](auto& keyValue)
		{
			auto& [playerId, player] = keyValue;
			player.Reset();
		});
	m_drawingString.clear();
}

void Game::PutScoresToDb()
{
	std::ranges::for_each(m_players, [&](const auto& keyValue)
		{
			const auto& [playerId, player] = keyValue;
			m_db->AddScore(std::move(player.GetScore()));
		});
}

uint16_t Game::GetTime() const
{
	if (m_gameState == GameState::Running)
		return m_roundTimer.GetElapsedTime();
	
	return kRoundDuration;
}

GameState Game::GetGameState() const
{
	return m_gameState;
}

int Game::GetOwnerId() const
{
	return m_ownerId;
}

std::string Game::GetDrawing() const
{
	return m_drawingString;
}

std::deque<Score> Game::GetScores() const
{
	std::deque<Score> scores;
	for (const auto& keyValue : m_players)
	{
		const auto& [playerId, player] = keyValue;
		scores.emplace_back(player.GetScore());
	}

	return scores;
}

int Game::GetPainterId() const
{
	return m_painterId;
}

std::string Game::GetWord(const int& playerId) const
{
	if (playerId == m_painterId)
		return m_currentWord.GetWord();

	return m_currentWord.GetVisibleCharacters();
}

std::deque<Player> Game::GetPlayers() const
{
	std::deque<Player> players;
	std::ranges::for_each(m_players, [&players](const auto& keyValue)
		{
			const auto& [id, player] = keyValue;
			players.emplace_back(player);
		});

	return players;
}
