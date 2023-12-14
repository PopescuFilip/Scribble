#include "routing.h"

using namespace ScribbleServer;

void Routing::Run(GameStorage& storage)
{
	CROW_ROUTE(m_app, "/")([]() {
		return "test";
		});

	m_app.port(18080).multithreaded().run();
}
