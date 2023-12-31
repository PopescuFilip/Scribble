#pragma once
#include "game.h"
#include <unordered_set>
import random;

namespace ScribbleServer
{

    class GameRoom {
    public:
        GameRoom(GameStorage& db);
    private:
        const std::string kRoomCode;
        static std::unordered_set<std::string> m_codes;
    };

}

