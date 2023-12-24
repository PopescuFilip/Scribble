#include "game.h"

using namespace ScribbleServer;

//ScribbleServer::Game::Game(GameStorage& db)
//{
//}

void Game::AddPlayer(const std::string& username)
{
}

void Game::Run()
{
}

void Game::RunOneRound(const int& painterId)
{
}

uint16_t Game::GetTime() const
{
    if (m_gameState == GameState::Running && roundTimer.IsActive()) 
    {
        return roundTimer.GetElapsedTime();
    }
    else
    {
        return 0;
    }
}
