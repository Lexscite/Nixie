#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <iostream>
#include <WinSock2.h>
#include <iostream>

#pragma comment(lib,"ws2_32.lib")

namespace NixieServer
{
	class Server
	{
	public:
		Server();
		~Server();

		bool Start();

	public:
		WSAData m_WSAData;
		WORD m_DllVersion;
		SOCKADDR_IN m_Address;
		SOCKET m_SocketListen;

		SOCKET m_Connections[100];
		int m_ConnectionCounter;
	};
}

#endif // !SERVER_H
