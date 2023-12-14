#pragma once
#include "gameDatabase.h"

namespace ScribbleServer
{
	class Routing
	{
	public:
		void Run(GameStorage& storage);

	private:
		crow::SimpleApp m_app;
	};
}


