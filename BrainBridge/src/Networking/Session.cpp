#include "pch.h"
#include "Session.h"

Session::Session()
{
	auto address = boost::asio::ip::make_address("127.0.0.1");
}
