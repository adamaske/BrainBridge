#pragma once


#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>


namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

//Using enable shared from this allows for this class to create a shared pointer to itself and expand its lifetime
class Session : public std::enable_shared_from_this<Session>
{
	
	//We need the io context
	net::io_context& mIoc;
	//a tcp reslover
	tcp::resolver mResolver;
	//The websocket connection
	websocket::stream<beast::ssl_stream<beast::tcp_stream>> mWs;
	//buffer for receiving messages
	beast::flat_buffer mBuffer;
	std::string mHost;
	std::string mText;
	std::string mEndpoint;
public:
	Session();

	void run() {
	};
};