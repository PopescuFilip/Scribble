#include "gameRoom.h"

using namespace ScribbleServer;

std::unordered_set<std::string> GameRoom::m_codes;

GameRoom::GameRoom(const std::shared_ptr<GameStorage>& db):
	m_game{ db },
	kRoomCode{ std::move(GetRandomUniqueCode(m_codes)) }
{
	m_codes.insert(kRoomCode);
}
