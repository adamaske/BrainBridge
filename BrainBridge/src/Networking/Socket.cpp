#include "pch.h"
#include "Socket.h"

#include <windows.h>
#include <winsock2.h>
#include <mstcpip.h	>
#include <ws2tcpip.h>
#include <rpc.h		>
#include <ntdsapi.h	>
#include "json/json.h"

Socket::Socket(SocketStream type)
{
	//To check if the socket gets created properly
	mSocket = INVALID_SOCKET;
	mType = type;
	if (mType == UDP) {
		//AF = address family spec(AF_INET is for UDP and TCP
		//type = The type spec for the new socket, SOCK_STREAM for TCP, SOCK_DGRAM for UDP
		//protocol = The protocol which is being used(IPPROTO_TCP for tcp)
		//Create this socket, UDP-TCP, UDP
		mSocket = ::socket(AF_INET, SOCK_DGRAM, 0);
	}
	else if(mType == TCP) {
		//Create this socket, UDP-TCP, TCP
		mSocket = ::socket(AF_INET, SOCK_STREAM, 0);
		mSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);
		if (mSocket == INVALID_SOCKET) {
			int result = WSAGetLastError();
			std::cout << "SocketClient : Socket Creation Error : " << result << "\n";
			return;
		}
		std::cout << "SocketClient : TCP Socket Created\n";
	}
}


SocketClient::SocketClient(SocketStream type, struct sockaddr* serverAddr, ULONG serverAddrLen, const SOCKET_SECURITY_SETTINGS* securitySettings, ULONG settingsLen) : Socket(type)
{
	//We have to do things differently for UDP and TCP
	if (mType == UDP) {
		//Just set mPeer to the address
		//mPeer = address;
	}
	else if (mType == TCP) {
	
		//The function returns an int based on the result
		int sockErr = WSASetSocketSecurity(mSocket, securitySettings, settingsLen, NULL, NULL);
		if (sockErr == SOCKET_ERROR) {
			//Something went wrong
			//This gets the last error WinSock got
			int result = WSAGetLastError();
			std::cout << "SocketClient : Securiy error : " << result << "\n";
		}
		std::cout << "SocketClient : Security enabled\n";

		//We can now connect the socket to the host
		//Because TCP requires comfirmation this will
		auto sockAddr = serverAddr;
		auto addrLen = sizeof(sockAddr) *2;
		sockaddr name;
		name.sa_family = AF_INET;
		sockErr = WSAConnect(mSocket, sockAddr, addrLen, NULL, NULL, NULL, NULL);
		//sockErr = ::connect(mSocket, (sockaddr*)&mPeer, sizeof(sockaddr));
		if (sockErr == SOCKET_ERROR) {
			//This will be tru if teh connection did not work
			std::cout << "ClientSocket : Connect failed " << WSAGetLastError() << "\n";
		}
		std::cout << "ClientSocket : Connection Succesfull!\n";
	}
	
}

//The client can send Bytes
void SocketClient::SendBytes(const std::string& bytes)
{
	std::cout << "SocketClient : SendBytes : \n";
	Json::Value params;
	params["id"] = 1;
	params["jsonrpc"] = 2.0;
	params["method"] = "getCortexInfo";
	Json::StreamWriterBuilder builder;
	const std::string json_file = Json::writeString(builder, params);
	//The buffer to send
	WSABUF wsaBuf = { 0 };
	wsaBuf.len =	json_file.length();
	wsaBuf.buf = const_cast<char*>(json_file.c_str());
	
	DWORD bytesSent = 0;
	std::cout << "SocketClient : Sending : Buffer = " << wsaBuf.buf << " : Length = " << wsaBuf.len << "\n";
	//Checks if there are any bytes to send
	if (bytes.size() == 0) {
		//Logger here
		std::cout << "SocketClient : Error : No bytes to send!\n";
	}
	if (mType == UDP) {
		//We can send away without caring 
		//what socket, the data, size of the data, no flags, what address, how much to read of the address
		::sendto(mSocket, bytes.c_str(), bytes.size(), 0, (sockaddr*)&mPeer, sizeof(sockaddr_in));
	}
	else if (mType == TCP) {
		WSASend(mSocket, &wsaBuf, 1, &bytesSent, 0, NULL, NULL);
	}

	//-----------------------------------------
	// Receive server's response securely

	DWORD bytesRecvd = 0;
	DWORD flags = 0;
	char recvBuf[2048] = { 0 };
	wsaBuf.len = 2048;
	wsaBuf.buf = recvBuf;
	int sockErr = WSARecv(mSocket, &wsaBuf, 1, &bytesRecvd, &flags, NULL, NULL);
	if (sockErr == SOCKET_ERROR) {
		std::cout << "SocketClient : WSARecv returned error " << WSAGetLastError() << "\n";
		
	}
	
	std::cout << "SocketClient : Recieved amount of bytes : " << bytesRecvd << "\n";

	std::cout << "SocketClient : Recieved bytes : " << wsaBuf.buf << "\n";
}

SocketServer::SocketServer(int port, int connections, SocketStream type) : Socket(type)
{
	WSADATA wsa;
	SOCKET s, new_socket;
	struct sockaddr_in server, client;

	//Create a socket
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}
	printf("Socket created.\n");

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8888);

	//Bind
	if (bind(s, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
	}

}

Socket* SocketServer::Accept()
{
	SOCKET sock = WSAAccept(mSocket, 0, 0, 0,0);

	if (sock == INVALID_SOCKET) {

	}
	return 0;
	
}
