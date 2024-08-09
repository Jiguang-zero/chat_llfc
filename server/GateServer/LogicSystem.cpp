#include "LogicSystem.h"

#include "HttpConnection.h"

bool LogicSystem::handleGet(std::string path, std::shared_ptr<HttpConnection> connection)
{
	if (get_handlers.find(path) == get_handlers.end())
	{
		return false;
	}
	get_handlers[path](connection);
	return true;
}

void LogicSystem::requestGet(std::string url, HttpHandler handler)
{
	get_handlers.insert(std::make_pair(url, handler));
}

LogicSystem::LogicSystem()
{
	requestGet("/get_test", [](std::shared_ptr<HttpConnection> connection)
		{
			beast::ostream(connection->response_.body()) << "receive get_test request";
		});
}

