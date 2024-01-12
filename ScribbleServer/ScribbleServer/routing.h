#pragma once
#include "game.h"

namespace ScribbleServer
{
	class Routing
	{
	public:
		void Run(std::shared_ptr<GameStorage> storage);
	private:
		crow::SimpleApp m_app;
		std::unordered_map<std::string, Game> m_games;

		std::unordered_set<std::string> m_codes;
	};
}


