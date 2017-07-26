#ifndef CLIENT_H
#define CLIENT_H

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <sstream>
#include <windows.h>
#include <vector>

#pragma comment(lib,"ws2_32.lib")

using namespace std;

enum PacketType
{
	PT_CHAT_MESSAGE,
};

namespace NixieClient
{
	class Client
	{
	public:
		Client();
		~Client();

		bool Connect();

		int Send(char* buffer, int bufferLength);
		int Recieve(char* buffer, int bufferLength);

		bool ProcessPacket(PacketType packetType);

	public:
		WSAData m_WSAData;
		WORD m_DllVersion;
		SOCKADDR_IN m_Address;

		SOCKET m_Connection;
	};
}

#endif // !CLIENT_H