#include "pch.h"
#include "Communicator.h"
#include "BrainBridge.h"


#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/strand.hpp>
namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
/*
 * To get a client id and a client secret, you must connect to your Emotiv
 * account on emotiv.com and create a Cortex app.
 * https://www.emotiv.com/my-account/cortex-apps/
 */
static const std::string ClientID = "1KkcmNkhTy22HiM2CMzXz03nnvGV1T7950LtMoEc";
static const std::string ClientSecret = "dPb5EplnkaRFt7AVs1PuNOrTBGsp3HTEXBnUlX4A86p1Ev1V6OI5KMuPbOvPbpXq4AYQ9m6pNNcOnCr2KK5ETLsGyX94rJxhAHauZhQb1ADEML7jyHWhXMxd3CHcwPRS";

// The name of the training profile used for the facial expression and mental command
static const std::string TrainingProfileName = "example";


int Communicator::Init()
{
    return 1;
}
bool Communicator::Connect()
{
    return false;
}
void Communicator::Request(const std::string& method)
{

}


