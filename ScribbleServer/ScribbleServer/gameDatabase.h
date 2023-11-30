#pragma once
//#include <string>
import word;
import round;
import player;
import score;
import user;

#include<sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;

namespace ScribbleServer
{
	inline auto CreateStorage(const std::string& filename)
	{
		return sql::make_storage(
			filename
			//tables
		);
	}
	
	using Storage = decltype(CreateStorage(""));

	class GameStorage
	{
	public:
		bool Initialize();

	private:
		void PopulateStorage();

	private:
		const std::string kDbFile{ "products.sqlite" };

	private:
		Storage m_db = CreateStorage(kDbFile);
	};
}



