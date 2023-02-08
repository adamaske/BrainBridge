#include "pch.h"
#include "WSListener.h"

WSListener::WSListener(/*net::io_context ioc, tcp::endpoint endpoint*/) //: mIoc(ioc), mAcceptor(ioc)
{
	//beast::error_code error;
	//
	////Open acceptor 
	//mAcceptor.open(endpoint.protocol(), error);
	//if (error) {
	//	//We have an error
	//}
	//
	////Address reuse
	//mAcceptor.set_option(net::socket_base::reuse_address(true), error);
	//
	////Bind to server address
	//mAcceptor.bind(endpoint, error);
	//
	////start listening
	//mAcceptor.listen(net::socket_base::max_listen_connections, error);
	//if (error) {
	//
	//}
	//




}

void WSListener::Run()
{
	Accept();
}

void WSListener::Accept()
{
	//mAcceptor.async_accept(net::make_strand(mIoc),
	//	beast::bind_front_handler(&WSListener::OnAccept));
}

void WSListener::OnAccept(beast::error_code err, tcp::socket socket)
{
	//A connection is accepted, make a session
}
