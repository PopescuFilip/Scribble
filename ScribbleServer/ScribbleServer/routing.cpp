#include "routing.h"
#include <thread>
import random;

using namespace ScribbleServer;

void Routing::Run(std::shared_ptr<GameStorage> storage)
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
			const int id{ std::stoi(std::move(stringId)) };

			const std::string newCode{ std::move(GetRandomUniqueCode(m_codes)) };

			m_codes.emplace(newCode);
			m_games.emplace(newCode, Game(storage, id));
			m_games.at(newCode).AddPlayer(id);
			
			return crow::response(200, newCode);

		});

	CROW_ROUTE(m_app, "/joinroom")([&](const crow::request& req)
		{
			const auto code{ req.url_params.get("code") };
			const std::string stringId{ req.url_params.get("id") };
			const int id{ std::stoi(std::move(stringId)) };

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
					playerJson["name"] = std::move(player.GetUsername());
					playerJson["score"] = std::move(player.GetScore().GetScoreValue());
					playersJson.push_back(playerJson);
				});

			return crow::json::wvalue{ playersJson };

		});

	CROW_ROUTE(m_app, "/start")([&](const crow::request& req) 
		{
			const auto code{ req.url_params.get("code") };
			const std::string stringId{ req.url_params.get("id") };
			const int id{ std::stoi(std::move(stringId)) };

			if (m_games.find(code) == m_games.end())
				return crow::response(404);

			if (m_games.at(code).GetOwnerId() != id)
				return crow::response(203);

			std::thread runThread([&](std::string code) { m_games.at(code).Run(); }, code);
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
			const int id{ std::stoi(std::move(stringId)) };

			if (m_games.find(code) == m_games.end())
				return crow::response(404);

			if (m_games.at(code).GetPainterId() != id)
				return crow::response(203);

			const auto drawingString{ req.url_params.get("drawing") };
			m_games.at(code).SetDrawing(drawingString);

			return crow::response(200);
		});

	CROW_ROUTE(m_app, "/checkstate")([&](const crow::request& req) 
		{
			const auto code{ req.url_params.get("code") };
			const std::string stringId{ req.url_params.get("id") };
			const int id{ std::stoi(std::move(stringId)) };

			crow::json::wvalue returnedJson;

			if (m_games.find(code) == m_games.end())
			{
				returnedJson["code"] = "404";
				return returnedJson;
			}

			bool canDraw = (m_games.at(code).GetPainterId() == id);
			const GameState gameState{ std::move(m_games.at(code).GetGameState()) };
			const std::string gameStateString{ std::move(GetStringFromGameState(gameState)) };
			
			returnedJson["code"] = "202";
			returnedJson["canDraw"] = crow::json::wvalue(canDraw);
			returnedJson["gameState"] = std::move(gameStateString);
			
			if (!canDraw)
				returnedJson["drawing"] = std::move(m_games.at(code).GetDrawing());

			return returnedJson;
		});

	CROW_ROUTE(m_app, "/getcandraw")([&](const crow::request& req)
		{
			const auto code{ req.url_params.get("code") };
			const std::string stringId{ req.url_params.get("id") };
			const int id{ std::stoi(std::move(stringId)) };

			if (m_games.find(code) == m_games.end())
				return crow::response(404);

			if (m_games.at(code).GetPainterId() != id)
				return crow::response(203);

			return crow::response(200);
		});

	CROW_ROUTE(m_app, "/getword")([&](const crow::request& req)
	{
		const auto code{ req.url_params.get("code") };
		const std::string stringId{ req.url_params.get("id") };
		const int id{ std::stoi(std::move(stringId)) };

		if (m_games.find(code) == m_games.end())
			return crow::response(404);

		return crow::response(200, std::move(m_games.at(code).GetWord(id)));
	});

	CROW_ROUTE(m_app, "/guessword")([&](const crow::request& req) 
		{
			const auto code{ req.url_params.get("code") };
			const std::string stringId{ req.url_params.get("id") };
			const int id{ std::stoi(stringId) };
			const auto word{ req.url_params.get("word") };

			if (m_games.find(code) == m_games.end())
				return crow::response(404);

			if (m_games.at(code).GuessWord(id, word))
				return crow::response(200, "correct");

			return crow::response(200, "incorrect");
		});

	CROW_ROUTE(m_app, "/profile")([&storage](const crow::request& req)
		{
			const std::string stringId{ req.url_params.get("id") };
			const int id{ std::stoi(stringId) };

			auto scores{ storage->GetLast5Scores(id) };

			std::vector<crow::json::wvalue> scoresJson;
			std::ranges::for_each(scores, [&scoresJson](const auto& score) 
				{
					crow::json::wvalue json;
					json["score"] = std::to_string(score.GetScoreValue());
					scoresJson.push_back(json);
				});
			
			return crow::json::wvalue{ scoresJson };

		});

	m_app.port(18080).multithreaded().run();
}
