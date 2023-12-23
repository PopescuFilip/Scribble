#include "game.h"


//ScribbleServer::Game::Game(GameStorage& db)
//{
//}

void ScribbleServer::Game::AddPlayer(const std::string& username)
{
}

void ScribbleServer::Game::Run()
{
}

void ScribbleServer::Game::RunOneRound(const int& painterId)
{
}

uint16_t ScribbleServer::Game::GetTime() const
{
    if (m_gameState == GameState::Running && roundTimer.IsActive()) {
        return roundTimer.GetElapsedTime();
    }
    else
    {
        return 0;
    }
}
