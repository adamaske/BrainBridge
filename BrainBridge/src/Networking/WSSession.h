#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/strand.hpp>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class WSSession {
public:
	tcp::resolver mResolver;
	websocket::stream<beast::tcp_stream> mWS;
	beast::flat_buffer mBuffer;
	std::string mHost;
	std::string mText;
	//The session needs only a ioc
	WSSession(net::io_context& ioc) {

	};

	void Run(const char* host, const char* port, char const* text) {
	//
		mHost = host;
		mText = text;

		//Look up domain
		mResolver.async_resolve(host, port, beast::bind_front_handler(&WSSession::mResolver));
	};
	void OnResolve(beast::error_code err, tcp::resolver::results_type result) {
		
		//When does this operation timeout
		beast::get_lowest_layer(mWS).expires_after(std::chrono::seconds(30));

		//Make connection on the IP address we got from a lookup
		beast::get_lowest_layer(mWS).async_connect(result, beast::bind_front_handler(&WSSession::OnConnect));
	};
	void OnConnect(beast::error_code err, tcp::resolver::results_type::endpoint_type ep) {

		//Turn of the tieount beacuse the websocket stream has its own timeout
		beast::get_lowest_layer(mWS).expires_never();

		//Suggested timeout for websocket, this is a client
		mWS.set_option(websocket::stream_base::timeout::suggested(beast::role_type::client));

		//
	}
};