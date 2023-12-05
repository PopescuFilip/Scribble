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
			)
		);
	}
	
	using Storage = decltype(CreateStorage(""));

	class GameStorage
	{
	public:
		bool Initialize();

		Word GetRandomWord();

	private:
		void PopulateStorage();

	private:
		const std::string kDbFile{ "products.sqlite" };
		const std::string kWordFile{ "words.txt" };

	private:
		Storage m_db = CreateStorage(kDbFile);
	};
}



