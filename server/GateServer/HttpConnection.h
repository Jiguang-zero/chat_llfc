#pragma once

#include <unordered_map>

#include "const.h"

/**
 * @brief http connection
 */
class HttpConnection : public std::enable_shared_from_this<HttpConnection>
{
public:
	friend class LogicSystem;
	HttpConnection(tcp::socket socket);
	void start();

private:
	void checkDeadline();
	void writeResponse();
	void handleRequest();
	void PreParseGetParam();
	tcp::socket socket_;
	beast::flat_buffer flat_buffer_{ 8192 };
	http::request<http::dynamic_body> request_;
	http::response<http::dynamic_body> response_;
	net::steady_timer deadline_{
		socket_.get_executor(), std::chrono::seconds(60)
	};

	std::string _get_url;
	std::unordered_map<std::string, std::string> _get_params;
};

