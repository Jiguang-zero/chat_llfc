#include "LogicSystem.h"
#include "HttpConnection.h"

#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include <string_view>
#include <boost/beast/core.hpp>
#include <boost/asio.hpp>

bool LogicSystem::handleGet(std::string path, std::shared_ptr<HttpConnection> connection)
{
	if (get_handlers.find(path) == get_handlers.end())
	{
		return false;
	}
	get_handlers[path](connection);
	return true;
}

bool LogicSystem::handlePost(std::string path, std::shared_ptr<HttpConnection> connection)
{
	if (post_handlers.find(path) == post_handlers.end())
	{
		return false;
	}
	post_handlers[path](connection);
	return true;
}

void LogicSystem::requestGet(std::string url, HttpHandler handler)
{
	get_handlers.insert(std::make_pair(url, handler));
}

void LogicSystem::requestPost(std::string url, HttpHandler handler)
{
	post_handlers.insert(std::make_pair(url, handler));
}

LogicSystem::LogicSystem()
{
	requestGet("/get_test", [](std::shared_ptr<HttpConnection> connection)
	{
		beast::ostream(connection->response_.body()) << "receive get_test request" << std::endl;
		int i = 0;
		for (auto & elem : connection->_get_params)
		{
			i++;
			beast::ostream(connection->response_.body()) << "param " << i << " key is " << elem.first;
			beast::ostream(connection->response_.body()) << "param " << i << " value is " << elem.second << std::endl;
		}
	});

	requestPost("/get_verify_code", [](std::shared_ptr<HttpConnection> connection)
	{
		auto body_str = boost::beast::buffers_to_string(connection->request_.body().data());
		std::cout << "receive body is " << body_str << std::endl;
		connection->response_.set(http::field::content_type, "text/json");
		Json::Value root;
		Json::Reader reader;
		Json::Value src_root;
		bool parse_success = reader.parse(body_str, src_root);
		if (!parse_success)
		{
			std::cout << "Failed to parse JSON data!" << std::endl;
			root["error"] = ErrorCodes::Error_Json;
			std::string json_str = root.toStyledString();
			beast::ostream(connection->response_.body()) << json_str;
			return true;
		}

		if (!src_root.isMember("email"))
		{
			std::cout << "Failed to parse JSON data!" << std::endl;
			root["error"] = ErrorCodes::Error_Json;
			std::string json_str = root.toStyledString();
			beast::ostream(connection->response_.body()) << json_str;
			return true;
		}


		auto email = src_root["email"].asString();
		std::cout << "email is " << email << std::endl;
		root["error"] = 0;
		root["email"] = src_root["email"];
		auto json_str = root.toStyledString();
		beast::ostream(connection->response_.body()) << json_str;
		return true;
	});
}

