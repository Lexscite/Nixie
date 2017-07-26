#ifndef SERVER_H
#define SERVER_H

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include <WinSock2.h>
#include <iostream>

#pragma comment(lib,"ws2_32.lib")

using namespace std;

enum PacketType
{
	PT_CHAT_MESSAGE,
};

namespace NixieServer
{
	class Server
	{
	public:
		Server();
		~Server();

		bool Start();

		int Send(char* buffer, int length, int id);
		int Recieve(char* buffer, int length, int id);

		bool ProcessPacket(int id, PacketType packetType);

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
