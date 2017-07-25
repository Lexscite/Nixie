#ifndef SERVER_H
#define SERVER_H

#include <windows.h>
#include <stdio.h>
#include <iostream>

#pragma comment(lib,"ws2_32.lib")

using namespace std;

namespace NixieServer
{
	class Server
	{
	public:
		Server();
		~Server();

		bool Start(int port);

		int Send(char* data, int length, int clientId);
		void SendToAll(char* data, int length, int clientId);
		int Recieve(char* data, int length, int clientId);

		bool CloseSocket();

	public:
		SOCKET m_Socket;
		SOCKET m_ClientSockets[10];
		SOCKADDR_IN m_SocketAddress;
		SOCKADDR_IN m_ClientSocketAddress;
		WSADATA m_SocketVersion;

		int m_NumCurrentClients;
		int m_NumMaxClients;
	};
}

#endif // !SERVER_H
