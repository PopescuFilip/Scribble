#pragma once
#include "gameDatabase.h"

namespace ScribbleServer
{
	class Routing
	{
	public:
		void Run(std::shared_ptr<GameStorage>& storage);

	private:
		crow::SimpleApp m_app;
	};
}


