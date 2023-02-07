#include "pch.h"
#include "Communicator.h"
#include "CortexCommunicator.h"
#include "BrainBridge.h"
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
    //The cortex creates its own io context
    int threads = 1;
    net::io_context ioc{ threads };

    //This listener will listen for connections to 
    auto listener = std::make_shared<WSListener>(ioc, tcp::endpoint{});
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
    sslc.use_private_key_file("src/rootCA.pem", ssl::context::pem);


    return false;
}
;