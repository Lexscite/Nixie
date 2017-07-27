#ifndef SERVER_H
#define SERVER_H

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>
#include <string>

#pragma comment(lib,"ws2_32.lib")

using namespace std;

enum PacketType
{
	PT_LOGIN_DATA,
	PT_CHAT_MESSAGE,
};

namespace NixieServer
{
	class Server
	{
	public:
		Server();
		~Server();

		bool Start(int port, bool broadcastPublically = false);

		bool ListenForNewConnection();


	private:
		int Send(int id, char* buffer, int length);
		int Recieve(int id, char* buffer, int length);

		bool SendInt(int id, int data);
		bool GetInt(int id, int &data);
		bool SendPacketType(int id, PacketType data);
		bool GetPacketType(int id, PacketType &data);
		bool SendString(int id, string &data);
		bool GetString(int id, string &data);

		bool ProcessPacket(int id, PacketType packetType);

		static void Thread(int id);

	private:
		SOCKET m_ListeningSocket;
		SOCKADDR_IN m_Address;
		int m_AddressSize;

		SOCKET m_Connections[100];
		int m_ConnectionCounter;
	};
}

#endif // !SERVER_H
