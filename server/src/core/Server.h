#ifndef __SERVER_H__
#define __SERVER_H__

#include <windows.h>
#include <vector>

#include "Connection.h"
#include "ChatMessage.h"

class CServer
{
public:
	static CServer* GetSingleton();
	
	bool Start(int port, bool isPublic = false);
	void Stop();
	void Run();

private:
	CServer();

	void KillConnection(int id);

	bool ProcessPacket(int id, PacketType _packetType);
	bool Send(int id, char* data, int totalBytes);
	bool Recieve(int id, char* data, int totalBytes);
	bool SendInt32(int id, int32_t data);
	bool GetInt32(int id, int32_t &data);
	bool SendPacketType(int id, PacketType data);
	bool GetPacketType(int id, PacketType &data);
	void SendString(int id, string &data);
	bool GetString(int id, string &data);

	static void ClientHandlerThread(int id);
	static void PacketSenderThread();

private:
	static CServer* s_singleton;

	bool m_isRunning;

	SOCKET m_socket;
	SOCKADDR_IN m_addr;
	int m_addrlen;

	std::vector<std::shared_ptr<CConnection>> m_pConnections;
	HANDLE m_hPacketSenderThread;
	mutex m_connectionsMutex;
	int  m_nUnusedConnections;
};

#endif