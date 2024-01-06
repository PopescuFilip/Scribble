#include "game.h"

using namespace ScribbleServer;


Game::Game(const std::shared_ptr<GameStorage>& db):
    m_db{ db },
    m_roundTimer{ kRoundDuration },
    m_gameState{ GameState::NotStarted }
{
}

void Game::AddPlayer(const int userId)
{
    auto sp = m_db.lock();
    User user{ sp->GetUser(userId) };
    m_players[userId] = Player{ user };
}

void Game::Run()
{
}

void Game::RunOneRound(const int& painterId)
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

Game::GameState Game::GetGameState() const
{
    return m_gameState;
}
