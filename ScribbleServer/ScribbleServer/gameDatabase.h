#pragma once
#include<iostream>
import word;
import round;
import player;
import score;
import user;

//#include<sqlite_orm/sqlite_orm.h>
//namespace sql = sqlite_orm;

namespace ScribbleServer
{
	class GameStorage
	{
	public:
		bool Initialize();

	private:
		const std::string kDbFile{ "products.sqlite" };

	};
}



