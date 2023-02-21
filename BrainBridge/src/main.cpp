#include "pch.h"

#include "BrainBridge.h"

//#include "json/json.h"

//#include <boost/asio.hpp>

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>

using tcp = boost::asio::ip::tcp;

//Using enable_shared:from this;

int main(int argc, char* argv[]) {

	auto const address = boost::asio::ip::make_address("127.0.0.1");
	auto const port = static_cast<unsigned short>(std::atoi("5800"));
    
	boost::asio::io_context ioc{1};

	tcp::acceptor acceptor{ ioc, {address, port} };
	
	while (1) {

		tcp::socket socket{ ioc };
		acceptor.accept(socket);

		std::cout << "Socket accepted\n";

		//Lock q
		std::thread{[q{std::move(socket)}]() mutable {
			//This thread uses one websocket
			boost::beast::websocket::stream<tcp::socket> ws{std::move(const_cast<tcp::socket&>(q))};
			//
			ws.set_option(boost::beast::websocket::stream_base::decorator(
				[](boost::beast::websocket::response_type& res) {
					
				}

			));
			//Wait for it to accept a connection
			ws.accept();
			//While the connection is active
			while (1) {
				try
				{
					//buffer
					boost::beast::flat_buffer buffer;
					ws.read(buffer);
					auto out = boost::beast::buffers_to_string(buffer.cdata());
					std::cout << out << "\n";

					//Echo
					ws.write(buffer.data());
				} //If the error code equals the closed code, the connection is over and we can break the while loop
				catch (const boost::beast::system_error& e)
				{
					//Relase while loop because the connection closed
					if (e.code() != boost::beast::websocket::error::closed) {
						std::cout << e.code().message() << "\n";
						break;
					}
				}
			}
		}
		
		}.detach();
	}
	ioc.run();
	std::cout << "Started Brain Bridge!\n";
	BrainBridge* app = new BrainBridge();
	//Int to store error code
	int err = 0;
	if (!err) {
		std::cout << "Main : BB Init Error!\n";
	}
	err = app->Run();
	if (!err) {
		std::cout << "Main : BB Run Init Error\n";
	}
	delete app;


	return 0;
}
