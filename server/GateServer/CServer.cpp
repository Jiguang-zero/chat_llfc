// ReSharper disable All
#include "CServer.h"

#include "HttpConnection.h"

CServer::CServer(boost::asio::io_context& ioc, unsigned short& port) : 
	_ioc(ioc), _acceptor(ioc, tcp::endpoint(tcp::v4(), port)), _socket(ioc)
{

}

void CServer::start()
{	
	auto self = shared_from_this();
	_acceptor.async_accept(_socket, [self](beast::error_code ec) {
		try
		{
			// 出错放弃这个链接，继续监听
			if (ec)
			{
				self->start();
				return;
			}

			std::make_shared<HttpConnection>(std::move(self->_socket))->start();

			self->start();
			
		} catch (std::exception& exp)
		{
			
		}
	});
}
