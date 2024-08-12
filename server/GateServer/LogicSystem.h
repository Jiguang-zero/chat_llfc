#pragma once

#include <map>

#include "Singleton.h"
#include "const.h"

class HttpConnection;
typedef std::function<void(std::shared_ptr<HttpConnection>)> HttpHandler;

class LogicSystem : public Singleton<LogicSystem>
{
	friend class Singleton<LogicSystem>;
public:
	~LogicSystem() {}
	bool handleGet(std::string, std::shared_ptr<HttpConnection>);
	bool handlePost(std::string, std::shared_ptr<HttpConnection>);
	void requestGet(std::string, HttpHandler handler);
	void requestPost(std::string, HttpHandler handler);
private:
	LogicSystem();
	std::map<std::string, HttpHandler> post_handlers;
	std::map<std::string, HttpHandler> get_handlers;
};

