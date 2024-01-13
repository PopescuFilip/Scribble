#include "Routes.h"

cpr::Response GetPlayers(const std::string& roomCode)
{
	return cpr::Get(
		cpr::Url{ "http://localhost:18080/getplayers" },
		cpr::Parameters{
		{ "code", roomCode }
		}
	);
}

cpr::Response GetGameState(const std::string& roomCode)
{
	return cpr::Get(
		cpr::Url{ "http://localhost:18080/gamestate" },
		cpr::Parameters{
		{ "code", roomCode }
		}
	);
}

cpr::Response GetWord(const int id, const std::string& roomCode)
{
	return cpr::Get(
		cpr::Url{ "http://localhost:18080/getword" },
		cpr::Parameters{
		{ "id", std::to_string(id) },
		{ "code", roomCode }
		}
	);
}

cpr::Response GuessWord(const int id, const std::string& roomCode, const std::string& word)
{
	return cpr::Get(
		cpr::Url{ "http://localhost:18080/guessword" },
		cpr::Parameters{
		{ "id", std::to_string(id) },
		{ "code", roomCode },
		{ "word", word }
		}
	);
}

cpr::Response GetProfile(const int id)
{
	return cpr::Get(
		cpr::Url{ "http://localhost:18080/profile" },
		cpr::Parameters{
		{ "id", std::to_string(id) }
		}
	);
}
