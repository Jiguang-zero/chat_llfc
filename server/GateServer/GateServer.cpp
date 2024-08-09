#include <iostream>
#include "CServer.h"

int main()
{
	try
	{
		unsigned short port = static_cast<unsigned short>(37111);
		net::io_context ioc{ 1 };
		boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);
		signals.async_wait([&ioc](const boost::system::error_code& error, int signal_number)
		{
			if (error)
			{
				return;
			}
			ioc.stop();
		});

		std::make_shared<CServer>(ioc, port)->start();
		ioc.run();
	}
	catch (std::exception const& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

    return 0;
}

//heap corruption detected: after normal block(#195) at 0x0000002607DDDBB0 CRT detected that the application wrote to the memory after end of heap buffer.