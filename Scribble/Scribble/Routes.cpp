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

cpr::Response CreateRoom(const int id)
{
	return cpr::Get(
		cpr::Url{ "http://localhost:18080/createroom" },
		cpr::Parameters{
			{ "id" , std::to_string(id) }
		}
	);;
}

cpr::Response JoinRoomRoute(const int id, const std::string& roomCode)
{
	return cpr::Get(
		cpr::Url{ "http://localhost:18080/joinroom" },
		cpr::Parameters{
		{ "id" , std::to_string(id) },
		{ "code", roomCode }
		}
	);
}

cpr::Response CheckState(const int id, const std::string& roomCode)
{
	return cpr::Get(
		cpr::Url{ "http://localhost:18080/checkstate" },
		cpr::Parameters{
		{ "id" , std::to_string(id) },
		{ "code", roomCode }
		}
	);
}

cpr::Response CheckUser(const std::string& user, const std::string& password)
{
	return cpr::Get(
		cpr::Url{ "http://localhost:18080/checkuser" },
		cpr::Parameters{
			{ "username" , user },
			{ "password", password }
		}
	);
}

cpr::Response AddUser(const std::string& user, const std::string& password)
{
	return cpr::Get(
		cpr::Url{ "http://localhost:18080/adduser" },
		cpr::Parameters{
			{ "username" , user },
			{ "password", password }
		}
	);
}

cpr::Response PutDrawing(const int id, const std::string& roomCode, const std::string& drawing)
{
	return cpr::Get(
		cpr::Url{ "http://localhost:18080/putdrawing" },
		cpr::Parameters{
		{ "id", std::to_string(id) },
		{ "code", roomCode },
		{ "drawing", drawing}
		}
	);
}

cpr::Response Start(const int id, const std::string& roomCode)
{
	return cpr::Get(
		cpr::Url{ "http://localhost:18080/start" },
		cpr::Parameters{
		{ "id" , std::to_string(id) },
		{ "code", roomCode }
		}
	);
}
