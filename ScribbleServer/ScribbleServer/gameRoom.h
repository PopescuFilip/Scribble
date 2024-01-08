#pragma once
#include "game.h"
import random;

namespace ScribbleServer
{

    class GameRoom 
    {
    public:
        GameRoom(const std::shared_ptr<GameStorage>& db);
    private:
        const std::string kRoomCode;
        Game m_game;

        static std::unordered_set<std::string> m_codes;
    };

}

