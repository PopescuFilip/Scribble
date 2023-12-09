#pragma once

import word;
import score;
import user;

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
				sql::make_column("id",&Score::SetScoreId, &Score::GetScoreId, sql::primary_key().autoincrement()),
				sql::make_column("username",&Score::SetUsername, &Score::GetUsername),
				sql::make_column("score",&Score::SetScore, &Score::GetScore)
			),
			sql::make_table(
				"User",
				sql::make_column("username", &User::SetUsername, &User::GetUsername, sql::primary_key()),
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

	private:
		void PopulateStorage();

	private:
		const std::string kDbFile{ "products.sqlite" };
		const std::string kWordFile{ "words.txt" };

	private:
		Storage m_db = CreateStorage(kDbFile);
	};
}



