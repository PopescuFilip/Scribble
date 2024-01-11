#include "routing.h"

using namespace ScribbleServer;

void Routing::Run(std::shared_ptr<GameStorage>& storage)
{
	CROW_ROUTE(m_app, "/")([]() 
		{
			return "test";
		});

	CROW_ROUTE(m_app, "/adduser")([&storage](const crow::request& req)
		{
			const auto newUsername{ req.url_params.get("username") };
			const auto newPassword{ req.url_params.get("password") };
			if (storage->AddUser(newUsername, newPassword))
				return crow::response(403);

			const int userId{ storage->GetUserId(newUsername) };

			return crow::response(200, std::to_string(userId));
		});

	CROW_ROUTE(m_app, "/checkuser")([&storage](const crow::request& req) 
		{
			const auto username{ req.url_params.get("username") };
			const auto password{ req.url_params.get("password") };

			if (storage->CheckUser(username, password))
				return crow::response(403);

			const int userId{ storage->GetUserId(username) };

			return crow::response(200, std::to_string(userId));

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
