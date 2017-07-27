#ifndef CLIENT_H
#define CLIENT_H

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <windows.h>
#include <string>

#pragma comment(lib,"ws2_32.lib")

using namespace std;

enum PacketType
{
	PT_LOGIN_DATA,
	PT_CHAT_MESSAGE,
};

namespace NixieClient
{

	class Client
	{
	public:
		Client();
		~Client();

		bool Init(string ip, int port);
		bool Connect();
		bool CloseConnection();

		bool SendPacketType(PacketType data);
		bool SendString(string &data);

	private:
		bool Send(char *data, int totalBytes);
		bool Recieve(char *data, int totalBytes);

		bool SendInt32(int32_t data);
		bool GetInt32(int32_t &data);
		bool GetPacketType(PacketType &data);
		bool GetString(string &data);

		bool ProcessPacket(PacketType packetType);
		static void Thread();

	private:
		SOCKET m_Connection;
		SOCKADDR_IN m_Address;
		int m_AddressSize;
	};
}

#endif // !CLIENT_H