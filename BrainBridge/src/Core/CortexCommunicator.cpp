#include "pch.h"
#include "Communicator.h"
#include "CortexCommunicator.h"
#include "../BrainBridge.h"



CortexCommunicator::CortexCommunicator(BrainBridge* own) : Communicator(own) {
    std::cout << "Cortex Communicator Created\n";
}
int CortexCommunicator::Init()
{
    int err = 0;
    auto const address = boost::asio::ip::make_address("127.0.0.1");
    auto const port = static_cast<unsigned short>(std::atoi("6868"));

    //Needed for every io operation
    boost::asio::io_context ioc{ 1 };

    //Acceptor for tcp, give v
    tcp::acceptor acceptor{ ioc, {address, port}};
    tcp::endpoint endpoint{ address, port };

    tcp::socket socket{ ioc };
    //Opens
    acceptor.open(endpoint.protocol());
    //
    acceptor.set_option(boost::asio::socket_base::reuse_address(true));
    std::cout << "Socket accepted!\n";

    acceptor.bind(endpoint);

    acceptor.listen(boost::asio::socket_base::max_listen_connections);

    while (1) {
        

        // The new connection gets its own strand
        //acceptor.async_accept(
        //    boost::asio::make_strand(ioc),
        //    boost::beast::bind_front_handler(
        //        &CortexCommunicator::OnAccept));
    }

    return 1;
}
bool CortexCommunicator::Connect()
{
    return false;
}

;

CortexWindow::CortexWindow()
{
}

CortexWindow::~CortexWindow()
{
}
