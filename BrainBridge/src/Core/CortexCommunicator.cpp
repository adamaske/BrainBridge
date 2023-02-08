#include "pch.h"
#include "Communicator.h"
#include "CortexCommunicator.h"
#include "BrainBridge.h"
#include "json/json.h"
#include "../Networking/WSListener.h"
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>
namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl;
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

CortexCommunicator::CortexCommunicator(BrainBridge* own) : Communicator(own) {
    std::cout << "Cortex Communicator Created\n";
}
int CortexCommunicator::Init()
{
    Connect();
    return 0;
    //The cortex creates its own io context
    int threads = 1;
    net::io_context ioc{ threads };

    //This listener will listen for connections to 
    auto listener = std::make_shared<WSListener>(/*ioc, tcp::endpoint{}*/);
    listener->Run();

    //For threads amount of threads, run ioc
    std::vector<std::thread> mThreads;
    for (int i = threads; i > 0; i--) {
        //lambda statement to for each thread to execute ioc.run
        mThreads.emplace_back([&ioc] { ioc.run(); });
    }
    //Dont know why this is done
    ioc.run();
    return 1;
}
bool CortexCommunicator::Connect()
{
    //Required for every io action
    net::io_context ioc;
    
    //We need a SSL context
    ssl::context sslc{ ssl::context::tlsv12_client };

    //Need the certificate
    sslc.load_verify_file("src/rootCA.pem");
    sslc.use_certificate_chain_file("src/rootCA.pem");
   // sslc.use_private_key_file("src/rootCA.pem", ssl::context::pem);

    //
    tcp::resolver resolver{ ioc };
    //This websocket stream is as beast::ssl tcp stream with ioc and sslc contexts
    websocket::stream<beast::ssl_stream<tcp::socket>> ws{ ioc, sslc };

    std::string host = "127.0.0.1";
    const auto port = "6868";
    const auto text = "{ {} : {}, {} : {}";
    Json::Value json;
    json["id"] = 1;
    json["jsonrpc"] = "2.0";
    json["method"] = "getCortexInfo";
    const auto t = json.toStyledString();
    //Find domain name
    const auto results = resolver.resolve(host, port);

    //Make the connection on the IP address we get from a lookup
    auto ep = net::connect(beast::get_lowest_layer(ws), results);

    //Set SNI hostname (many hosts need this to handshake
    if (!SSL_set_tlsext_host_name(ws.next_layer().native_handle(), host.c_str())){
        "Failed to get hostname";
    }

    //Update host string. This will provde the value of the Host HTTP header during the websocket handskae
    host += ':' + std::to_string(ep.port());

    //Perform ssl handshake
    ws.next_layer().handshake(ssl::stream_base::client);

    //Set a decorator to change the UserAgent of the handshake
    ws.set_option(websocket::stream_base::decorator(
        [](websocket::request_type& req) {
            req.set(http::field::user_agent, std::string(BOOST_BEAST_VERSION_STRING) + " websocket-client-coro");
        }));

    //Perform handshakes
    ws.handshake(host, "/");

    //Send message
    ws.write(net::buffer(std::string(t)));

    //This buffer holds incoming
    beast::flat_buffer buffer;


    //Read
    ws.read(buffer);

    //close
    ws.close(websocket::close_code::normal);

    //If we get here the connection is closed
    std::cout << beast::make_printable(buffer.data()) << "\n";
 
    return false;
}
;