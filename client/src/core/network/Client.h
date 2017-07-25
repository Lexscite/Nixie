#ifndef CLIENT_H
#define CLIENT_H

#include <windows.h>
#include <stdio.h> 
#include <iostream>

#pragma comment(lib,"ws2_32.lib")

using namespace std;

namespace NixieClient
{
	class Client
	{
	public:
		Client();
		~Client();

		bool Connect(char* ip, int port);

		int Send(char* data, int length, int clientId);
		int Recieve(char* data, int length, int clientId);

		bool CloseSocket();

	public:
		SOCKET m_Socket;
		SOCKADDR_IN m_SocketAddress;
		WSADATA m_SocketVersion;
	};
}

#endif // !CLIENT_H