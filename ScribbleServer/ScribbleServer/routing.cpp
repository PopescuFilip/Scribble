#include "routing.h"

using namespace ScribbleServer;

void Routing::Run(std::shared_ptr<GameStorage>& storage)
{
	CROW_ROUTE(m_app, "/")([]() 
		{
			return "test";
		});

	CROW_ROUTE(m_app, "/gamestate")([&](const crow::request& req) 
		{
			const auto code{ req.url_params.get("code") };

			try
			{
				const GameState gameState{ std::move(m_games.at(code).GetGameState()) };
				const std::string gameStateString{ std::move(GetStringFromGameState(gameState)) };
				return crow::response(200, gameStateString);
			}
			catch (...)
			{
				return crow::response(404);
			}
		});

	m_app.port(18080).multithreaded().run();
}
