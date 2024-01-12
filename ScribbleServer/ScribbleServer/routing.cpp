#include "routing.h"
#include <thread>
import random;

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
			if (!storage->AddUser(newUsername, newPassword))
				return crow::response(403);

			const int userId{ storage->GetUserId(newUsername) };

			return crow::response(200, std::to_string(userId));
		});

	CROW_ROUTE(m_app, "/checkuser")([&storage](const crow::request& req) 
		{
			const auto username{ req.url_params.get("username") };
			const auto password{ req.url_params.get("password") };

			if (!storage->CheckUser(username, password))
				return crow::response(403);

			const int userId{ storage->GetUserId(username) };

			return crow::response(200, std::to_string(userId));

		});

	CROW_ROUTE(m_app, "/createroom")([&](const crow::request& req) 
		{
			const std::string stringId{ req.url_params.get("id") };
			const int id{ std::stoi(stringId) };

			const std::string newCode{ GetRandomUniqueCode(m_codes) };
			m_codes.emplace(newCode);
			m_games.emplace(newCode, Game(storage, id));
			m_games.at(newCode).AddPlayer(id);
			
			return crow::response(200, newCode);

		});

	CROW_ROUTE(m_app, "/joinroom")([&](const crow::request& req)
		{
			const auto code{ req.url_params.get("code") };
			const std::string stringId{ req.url_params.get("id") };
			const int id{ std::stoi(stringId) };

			if (m_games.find(code) == m_games.end())
				return crow::response(404);

			m_games.at(code).AddPlayer(id);

			return crow::response(200);

		});

	CROW_ROUTE(m_app, "/getplayers")([&](const crow::request& req)
		{
			const auto code{ req.url_params.get("code") };

			const auto players{ m_games.at(code).GetPlayers() };

			std::vector<crow::json::wvalue> playersJson;
			std::ranges::for_each(players, [&playersJson](const auto& player)
				{
					crow::json::wvalue playerJson;
					playerJson["name"] = player.GetUsername();
					playersJson.push_back(playerJson);
				});

			return crow::json::wvalue{ playersJson };

		});

	CROW_ROUTE(m_app, "/start")([&](const crow::request& req) 
		{
			const auto code{ req.url_params.get("code") };
			const std::string stringId{ req.url_params.get("id") };
			const int id{ std::stoi(stringId) };

			if (m_games.find(code) == m_games.end())
				return crow::response(404);

			if (m_games.at(code).GetOwnerId() != id)
				return crow::response(203);

			std::thread runThread([&](std::string code) {m_games.at(code).Run(); }, code);

			runThread.detach();

			return crow::response(200);
		});

	CROW_ROUTE(m_app, "/gamestate")([&](const crow::request& req) 
		{
			const auto code{ req.url_params.get("code") };

			if (m_games.find(code) == m_games.end())
				return crow::response(404);
			
			const GameState gameState{ std::move(m_games.at(code).GetGameState()) };
			const std::string gameStateString{ std::move(GetStringFromGameState(gameState)) };
			return crow::response(200, gameStateString);
		});

	CROW_ROUTE(m_app, "/putdrawing")([&](const crow::request& req)
		{
			const auto code{ req.url_params.get("code") };
			const std::string stringId{ req.url_params.get("id") };
			const int id{ std::stoi(stringId) };

			if (m_games.find(code) == m_games.end())
				return crow::response(404);

			if (m_games.at(code).GetPainterId() != id)
				return crow::response(203);

		});

	CROW_ROUTE(m_app, "/getdrawing")([&](const crow::request& req) 
		{
			const auto code{ req.url_params.get("code") };
			const std::string stringId{ req.url_params.get("id") };
			const int id{ std::stoi(stringId) };

			if (m_games.find(code) == m_games.end())
				return crow::response(404);

			if (m_games.at(code).GetPainterId() == id)
				return crow::response(203);
			
			/*std::vector<crow::json::wvalue> drawingJson;
			for (const auto& line : m_games.at(code).GetDrawing())
			{
				const auto& [firstPoint, secondPoint] = line;
				const auto& [firstPointX, firstPointY] = firstPoint;
				const auto& [secondPointX, secondPointY] = secondPoint;

				crow::json::wvalue json;
				json["firstPointX"] = std::to_string(firstPointX);
				json["firstPointY"] = std::to_string(firstPointY);
				json["secondPointX"] = std::to_string(secondPointX);
				json["secondPointY"] = std::to_string(secondPointY);
				drawingJson.push_back(json);

			}

			return crow::json::wvalue{ drawingJson };*/
		});



	

	m_app.port(18080).multithreaded().run();
}

//std::string Routing::DrawingToString(const std::deque<Game::Line>& vec)
//{
//	std::stringstream ss;
//	ss << "nodes=";
//	for (size_t i = 0; i < vec.size(); ++i)
//	{
//		const auto& [firstPoint, secondPoint] = vec[i];
//		const auto& [firstX, firstY] = firstPoint;
//		const auto& [secondX, secondY] = secondPoint;
//
//		ss << firstX << " " << firstY << " " << secondX << " " << secondY;
//		if (i == vec.size() - 1)
//			break;
//		ss << ",";
//	}
//	return ss.str();
//}
