#include "pch.h"

#include "BrainBridge.h"

#include "json/json.h"


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



class CortexSession : public Session {
public:
	CortexSession();
	~CortexSession();

private:

#pragma region RootCA Perm - Certification
	std::string cert = "-----BEGIN CERTIFICATE-----\n"
		"MIIE6zCCA9OgAwIBAgIJAKvjTcU7786lMA0GCSqGSIb3DQEBCwUAMIGpMQswCQYD"
		"VQQGEwJVUzETMBEGA1UECBMKQ2FsaWZvcm5pYTEWMBQGA1UEBxMNU2FuIEZyYW5j"
		"aXNjbzEUMBIGA1UEChMLRW1vdGl2IEluYy4xFDASBgNVBAsTC1dlYlNlcnZpY2Vz"
		"MR0wGwYDVQQDExRFbW90aXYgTG9jYWwgQ0EgUm9vdDEiMCAGCSqGSIb3DQEJARYT"
		"bm8tcmVwbHlAZW1vdGl2LmNvbTAeFw0xODEyMTAxNjM0NDhaFw0yMzEyMDkxNjM0"
		"NDhaMIGpMQswCQYDVQQGEwJVUzETMBEGA1UECBMKQ2FsaWZvcm5pYTEWMBQGA1UE"
		"BxMNU2FuIEZyYW5jaXNjbzEUMBIGA1UEChMLRW1vdGl2IEluYy4xFDASBgNVBAsT"
		"C1dlYlNlcnZpY2VzMR0wGwYDVQQDExRFbW90aXYgTG9jYWwgQ0EgUm9vdDEiMCAG"
		"CSqGSIb3DQEJARYTbm8tcmVwbHlAZW1vdGl2LmNvbTCCASIwDQYJKoZIhvcNAQEB"
		"BQADggEPADCCAQoCggEBAMGQcVYpbWyO5+oWqDWM45SuL+nJOQ3zRRWGo3BiQIsh"
		"O5kiFR5b7VZm2Er2KxioqrTOgbug7i8hYK3IGOCvDkR29TVx+D82kLLqXngGfRDa"
		"hYSsojVe8P1BFUgEV+ZLBCiuTvjibR1lvFFy68ytR6vh8m5NI6Vb2Qm94tAC7KXD"
		"OiTYdD5M/LwjafR+tqoz1bXdAgNcP9msIR9VFZ5GffVwa9spNnGqMnoHQNv8m5EC"
		"cswefgUO8vGGhHf6SF6eHdTXjnj1UYQvHipvMf709JxoahRpAX/ucUszkqGl72yV"
		"tH1wc1YvkJ9bdHPGOZeLv8AcuI/lEQoLU8YyWkhbiMkCAwEAAaOCARIwggEOMB0G"
		"A1UdDgQWBBTWstU5lnlIeilsWPvWQPx+s3MlRTCB3gYDVR0jBIHWMIHTgBTWstU5"
		"lnlIeilsWPvWQPx+s3MlRaGBr6SBrDCBqTELMAkGA1UEBhMCVVMxEzARBgNVBAgT"
		"CkNhbGlmb3JuaWExFjAUBgNVBAcTDVNhbiBGcmFuY2lzY28xFDASBgNVBAoTC0Vt"
		"b3RpdiBJbmMuMRQwEgYDVQQLEwtXZWJTZXJ2aWNlczEdMBsGA1UEAxMURW1vdGl2"
		"IExvY2FsIENBIFJvb3QxIjAgBgkqhkiG9w0BCQEWE25vLXJlcGx5QGVtb3Rpdi5j"
		"b22CCQCr403FO+/OpTAMBgNVHRMEBTADAQH/MA0GCSqGSIb3DQEBCwUAA4IBAQBs"
		"6IOUHbepN1+2PGbBdQ7H/IGdpAZlnOX0LRmHf1wzsv0sdwCo+OWfjYH9j08F+xpS"
		"+pmQsK4ENDTn+COuhR/EyiBkzvIKwR2lZMv/iNGvV4JccCS5A0h67XR2IHYTCKpg"
		"WFyc+UtHlZbe7DLo/pREtE0PAUoIYNCVeG7f+HaePRpEqSjjX5VIGAAPIkZ8SHfW"
		"HGeG0mrn+8a6l5WlDAQs6agAHkZ6L30hQqMiw7Y7x5r2bDbAT5IGLDtxvh8FOYol"
		"aPfP6o/5odNZM2X3YD7PuQ48m7qtnqqLe1mj8t90C8z/UhV4Am/cTRFSBhEig/25"
		"2vGyHmMfhPgMK48PGWmd\n"
		"-----END CERTIFICATE-----\n";
#pragma endregion


};
void LoadTrainingProfiles() {
	Json::Value val;
	val["id"] = 1;
	val["jsonrpc"] = "2.0";
	val["method"] = "queryProfiles";
}

int main(int argc, char* argv[]) {

	std::cout << "Started Brain Bridge!\n";
	BrainBridge* app = new BrainBridge();
	//Int to store error code
	int err = 0;
	err = app->Init();
	if (!err) {
		std::cout << "Main : BB Init Error!\n";
	}
	err = app->Run();
	if (!err) {
		std::cout << "Main : BB Run Error\n";
	}
	delete app;


	return 0;

	int threads = 1;
	//Start with an io context

	try
	{
		auto address = boost::asio::ip::make_address("127.0.0.1");
		//auto port = (std::atoi("6868"));
		Json::Value val;
		val["id"] = 1;
		val["jsonrpc"] = "2.0";
		val["method"] = "requestAccess";
		auto text = "tøys";
		//Io context
		net::io_context ioc{ threads };

		//The SSL context is required, and holds certificates
		ssl::context ctx{ ssl::context::tlsv12_client };
		ctx.set_options(
			boost::asio::ssl::context::default_workarounds |
			boost::asio::ssl::context::no_sslv2 |
			boost::asio::ssl::context::single_dh_use);

		std::string cert = "-----BEGIN CERTIFICATE-----\n"
			"MIIE6zCCA9OgAwIBAgIJAKvjTcU7786lMA0GCSqGSIb3DQEBCwUAMIGpMQswCQYD"
			"VQQGEwJVUzETMBEGA1UECBMKQ2FsaWZvcm5pYTEWMBQGA1UEBxMNU2FuIEZyYW5j"
			"aXNjbzEUMBIGA1UEChMLRW1vdGl2IEluYy4xFDASBgNVBAsTC1dlYlNlcnZpY2Vz"
			"MR0wGwYDVQQDExRFbW90aXYgTG9jYWwgQ0EgUm9vdDEiMCAGCSqGSIb3DQEJARYT"
			"bm8tcmVwbHlAZW1vdGl2LmNvbTAeFw0xODEyMTAxNjM0NDhaFw0yMzEyMDkxNjM0"
			"NDhaMIGpMQswCQYDVQQGEwJVUzETMBEGA1UECBMKQ2FsaWZvcm5pYTEWMBQGA1UE"
			"BxMNU2FuIEZyYW5jaXNjbzEUMBIGA1UEChMLRW1vdGl2IEluYy4xFDASBgNVBAsT"
			"C1dlYlNlcnZpY2VzMR0wGwYDVQQDExRFbW90aXYgTG9jYWwgQ0EgUm9vdDEiMCAG"
			"CSqGSIb3DQEJARYTbm8tcmVwbHlAZW1vdGl2LmNvbTCCASIwDQYJKoZIhvcNAQEB"
			"BQADggEPADCCAQoCggEBAMGQcVYpbWyO5+oWqDWM45SuL+nJOQ3zRRWGo3BiQIsh"
			"O5kiFR5b7VZm2Er2KxioqrTOgbug7i8hYK3IGOCvDkR29TVx+D82kLLqXngGfRDa"
			"hYSsojVe8P1BFUgEV+ZLBCiuTvjibR1lvFFy68ytR6vh8m5NI6Vb2Qm94tAC7KXD"
			"OiTYdD5M/LwjafR+tqoz1bXdAgNcP9msIR9VFZ5GffVwa9spNnGqMnoHQNv8m5EC"
			"cswefgUO8vGGhHf6SF6eHdTXjnj1UYQvHipvMf709JxoahRpAX/ucUszkqGl72yV"
			"tH1wc1YvkJ9bdHPGOZeLv8AcuI/lEQoLU8YyWkhbiMkCAwEAAaOCARIwggEOMB0G"
			"A1UdDgQWBBTWstU5lnlIeilsWPvWQPx+s3MlRTCB3gYDVR0jBIHWMIHTgBTWstU5"
			"lnlIeilsWPvWQPx+s3MlRaGBr6SBrDCBqTELMAkGA1UEBhMCVVMxEzARBgNVBAgT"
			"CkNhbGlmb3JuaWExFjAUBgNVBAcTDVNhbiBGcmFuY2lzY28xFDASBgNVBAoTC0Vt"
			"b3RpdiBJbmMuMRQwEgYDVQQLEwtXZWJTZXJ2aWNlczEdMBsGA1UEAxMURW1vdGl2"
			"IExvY2FsIENBIFJvb3QxIjAgBgkqhkiG9w0BCQEWE25vLXJlcGx5QGVtb3Rpdi5j"
			"b22CCQCr403FO+/OpTAMBgNVHRMEBTADAQH/MA0GCSqGSIb3DQEBCwUAA4IBAQBs"
			"6IOUHbepN1+2PGbBdQ7H/IGdpAZlnOX0LRmHf1wzsv0sdwCo+OWfjYH9j08F+xpS"
			"+pmQsK4ENDTn+COuhR/EyiBkzvIKwR2lZMv/iNGvV4JccCS5A0h67XR2IHYTCKpg"
			"WFyc+UtHlZbe7DLo/pREtE0PAUoIYNCVeG7f+HaePRpEqSjjX5VIGAAPIkZ8SHfW"
			"HGeG0mrn+8a6l5WlDAQs6agAHkZ6L30hQqMiw7Y7x5r2bDbAT5IGLDtxvh8FOYol"
			"aPfP6o/5odNZM2X3YD7PuQ48m7qtnqqLe1mj8t90C8z/UhV4Am/cTRFSBhEig/25"
			"2vGyHmMfhPgMK48PGWmd\n"
			"-----END CERTIFICATE-----\n";
		boost::asio::const_buffer buf(cert.data(), cert.size());
		
		boost::system::error_code ec;
		ctx.use_certificate(buf, ssl::context_base::pem);
		//ctx.add_certificate_authority(
		//	boost::asio::buffer(cert.data(), cert.size()), ec);
		//load_root_certficates(ctx);
		if (ec) {
			std::cout << ec.what() << "\n";
		}
		tcp::resolver resolver{ ioc };
		websocket::stream<beast::ssl_stream<tcp::socket>> ws{ ioc, ctx };

		std::string host = "127.0.0.1";
		//Domain name
		auto results = resolver.resolve(host, "6868");

		//Make the connection on the ip we get from a lookup
		auto ep = net::connect(get_lowest_layer(ws), results);

		//Set SNI hostname (many hosts need this to handshake successfully
		if(!SSL_set_tlsext_host_name(ws.next_layer().native_handle(), host.c_str()))
			throw beast::system_error(
				beast::error_code(
					static_cast<int>(::ERR_get_error()),
					net::error::get_ssl_category()),
				"Failed to set SNI Hostname");

		//Update the host_ string, this will provide the value of the Host http header during the Wbeoscket hanshake.
		//See https://tools.ietf.org/html/rfc7230#section-5.4
		host += ':' + std::to_string(ep.port());

		//Perform the SSL handhsake
		ws.next_layer().handshake(ssl::stream_base::client);

		//Set a decorator to change the user agent of the handshake
		ws.set_option(websocket::stream_base::decorator([](websocket::request_type& req) {
			req.set(http::field::user_agent, std::string(BOOST_BEAST_VERSION_STRING) + " websocket-client-coro");
			}));

		//Perform the handhsake,
		ws.handshake(host, "/");
		Json::Value value;
		value["id"] = 1;
		value["jsonrpc"] = "2.0";
		value["method"] = "getCortexInfo";
		ws.write(net::buffer(value.toStyledString()));
		beast::flat_buffer buffer;

		ws.read(buffer);

		//ws.close(websocket::close_code::normal);

		std::cout << beast::make_printable(buffer.data()) << "\n";
	}
	catch (std::exception const& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return BB_ERROR;
	}
	return 0;

	
}
