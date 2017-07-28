#ifndef SERVER_H
#define SERVER_H

#include <windows.h>
#include <vector>

#include "Connection.h"
#include "ChatMessage.h"

using std::cout;
using std::endl;
using std::vector;
using std::shared_ptr;

namespace NixieServer
{
	class Server
	{
	public:
		Server();
		~Server();

		bool Start(int port, bool broadcastPublically = false);

		bool Run();

	private:
		void DisconnectClient(int id);

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

		vector<shared_ptr<Connection>> m_pConnections;
		mutex m_ConnectionMutex;
		int  m_NumUnusedConnections;
	};
}

#endif // !SERVER_H
