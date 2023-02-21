#include "pch.h"

#include "json/json.h"

#include "BrainBridge.h"
//#include "json/json.h"


#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/bind_executor.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/make_unique.hpp>
#include <boost/config.hpp>
using tcp = boost::asio::ip::tcp;               // from <boost/asio/ip/tcp.hpp>
namespace ssl = boost::asio::ssl;               // from <boost/asio/ssl.hpp>
namespace websocket = boost::beast::websocket;  // from <boost/beast/websocket.hpp>
namespace net = boost::asio;
//#include <boost/asio.hpp>
static const std::string ClientID = "1KkcmNkhTy22HiM2CMzXz03nnvGV1T7950LtMoEc";
static const std::string ClientSecret = "dPb5EplnkaRFt7AVs1PuNOrTBGsp3HTEXBnUlX4A86p1Ev1V6OI5KMuPbOvPbpXq4AYQ9m6pNNcOnCr2KK5ETLsGyX94rJxhAHauZhQb1ADEML7jyHWhXMxd3CHcwPRS";

Json::Value CortexBaseCall() {
	Json::Value val;
	val["id"] = 1;
	val["jsonrpc"] = "2.0";
	return val;
}

Json::Value CortexRequestAccessValue() {
	Json::Value val = CortexBaseCall();
	val["method"] = "requestAccess";
	Json::Value parms;
	parms["clientId"] = ClientID;
	parms["clientSecret"] = ClientSecret;
	val["params"] = parms;
	return val;
}
Json::Value CortexMethodCall() {
	
	return Json::Value();
}


void RequestAccess() {
	std::cout << "Request Access\n";
}

int main(int argc, char* argv[]) {

	//First an io context
	net::io_context ioc;
	
	//We want a connection on a socket
	net::ip::tcp::socket sock(ioc);

	net::const_buffer payload;
	//
	auto bytes_transferred = boost::asio::write(sock, payload);

	//Connect to cortex
	//	Request Access
	//	Gain token
	
	//Connect to Unreal Engine
	//	Set ports and ips
	//	
	// 
	//Testing
	std::unordered_map<std::string, std::function<void()>> mScreens;
	mScreens["RequestAccess"] = std::function<void()>(RequestAccess);
	mScreens["RequestAccess"] = []() { std::cout << "RequestAccess from labda\n"; };
	mScreens["RequestAccess"]();
	//auto requestAccessJson = CortexRequestAccessValue();
	//auto stringied = requestAccessJson.asCString();

	//Cortex stuff


	//

	return 0;
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
