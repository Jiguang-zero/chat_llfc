#include "HttpConnection.h"
#include "LogicSystem.h"

#include <iostream>

HttpConnection::HttpConnection(tcp::socket socket) : socket_(std::move(socket))
{
}

void HttpConnection::start()
{
	auto self = shared_from_this();
	http::async_read(socket_, flat_buffer_, request_, [self](beast::error_code ec, std::size_t bytes_transferred)
	{
		try
		{
			if (ec)
			{
				std::cout << "http read err is " << ec.what() << std::endl;
				return;
			}

			boost::ignore_unused(bytes_transferred);
			self->handleRequest();
			self->checkDeadline();
		}
		catch (std::exception& exp)
		{
			std::cout << "exception is " << exp.what() << '\n';
		}
	});
}

void HttpConnection::checkDeadline()
{
	auto self = shared_from_this();
	deadline_.async_wait([self](beast::error_code ec)
	{
		if (!ec)
		{
			self->socket_.close(ec);
		}
	});
}

void HttpConnection::writeResponse()
{
	auto self = shared_from_this();
	response_.content_length(response_.body().size());
	http::async_write(socket_, response_, [self](beast::error_code ec, std::size_t bytes_transferred)
	{
			self->socket_.shutdown(tcp::socket::shutdown_send, ec);
			self->deadline_.cancel();
	});
}

void HttpConnection::handleRequest()
{
	// set the version
	response_.version(request_.version());
	response_.keep_alive(false);
	if (request_.method() == http::verb::get)
	{
		bool success = LogicSystem::getInstance()->handleGet(request_.target(), shared_from_this());
		if (!success)
		{
			response_.result(http::status::not_found);
			response_.set(http::field::content_type, "text/plain");
			beast::ostream(response_.body()) << "url not found\r\n";
			writeResponse();
			return;
		}

		response_.result(http::status::ok);
		response_.set(http::field::server, "GateServer");
		writeResponse();

		return;
	}
}
