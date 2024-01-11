#pragma once
import word;
import score;
import user;
import utils;


#include <crow.h>
#include<sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;

namespace ScribbleServer
{
	inline auto CreateStorage(const std::string& filename)
	{
		return sql::make_storage(
			filename,
			sql::make_table(
				"Words",
				sql::make_column("id", &Word::SetWordId, &Word::GetWordId, sql::primary_key().autoincrement()),
				sql::make_column("word", &Word::SetWord, &Word::GetWord)
			),
			sql::make_table(
				"Score",
				sql::make_column("id", &Score::SetScoreId, &Score::GetScoreId, sql::primary_key().autoincrement()),
				sql::make_column("user_id", &Score::SetUserId, &Score::GetUserId),
				sql::make_column("score", &Score::SetScore, &Score::GetScore)
			),
			sql::make_table(
				"User",
				sql::make_column("user_id", &User::SetUserId, &User::GetUserId, sql::primary_key().autoincrement()),
				sql::make_column("username", &User::SetUsername, &User::GetUsername),
				sql::make_column("password", &User::SetPassword, &User::GetPassword)
			)
		);
	}
	
	using Storage = decltype(CreateStorage(""));

	class GameStorage
	{
	public:
		bool Initialize();

		Word GetRandomWord();
		std::vector<Word> GetWords();
		std::vector<User> GetUsers();

		User GetUser(const int userId);
		int GetUserId(const std::string& username);

		void AddScore(const Score& score);
		bool AddUser(std::string username, std::string password);
		
		bool CheckUser(const User& user);
		bool UsernameExists(const std::string& username);

		std::vector<Score> GetLast5Scores(const int& userId);

	private:
		void PopulateStorage();

		void AddUser(const User& user);

	private:
		const std::string kDbFile{ "scribble.sqlite" };
		const std::string kWordFile{ "words.txt" };

	private:
		Storage m_db = CreateStorage(kDbFile);
	};


	class AddToUserHandler
	{
	public:
		AddToUserHandler(GameStorage& storage);

		crow::response operator() (const crow::request& req) const;

	private:
		GameStorage& m_db;
	};
}



