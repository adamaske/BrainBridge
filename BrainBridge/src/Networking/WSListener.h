#pragma once


#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class WSListener {
public:
	WSListener(net::io_context ioc, tcp::endpoint endpoint);

	net::io_context &mIoc;
	tcp::acceptor mAcceptor;

	void Run();

	void Accept();
	void OnAccept(beast::error_code err, tcp::socket socket);
};