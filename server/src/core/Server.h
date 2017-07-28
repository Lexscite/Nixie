#ifndef SERVER_H
#define SERVER_H

#include "PacketManager.h"
#include <windows.h>

using std::cout;
using std::endl;

namespace NixieServer
{
	struct Connection
	{
		SOCKET socket;
		PacketManager packetManager;
	};

	class Server
	{
	public:
		Server();
		~Server();

		bool Start(int port, bool broadcastPublically = false);

		bool Run();

	private:
		bool Send(int id, char* data, int totalBytes);
		bool Recieve(int id, char* data, int totalBytes);

		bool SendInt32(int id, int32_t data);
		bool GetInt32(int id, int32_t &data);
		bool SendPacketType(int id, PacketType data);
		bool GetPacketType(int id, PacketType &data);
		void SendString(int id, string &data);
		bool GetString(int id, string &data);

		bool ProcessPacket(int id, PacketType _packetType);

		static void ClientHandlerThread(int id);
		static void PacketSenderThread();

	private:
		SOCKET m_ListeningSocket;
		SOCKADDR_IN m_Address;
		int m_AddressSize;

		Connection m_Connections[100];
		int m_ConnectionCounter;
	};
}

#endif // !SERVER_H
