#ifndef __SERVER_H__
#define __SERVER_H__

#pragma once

#include <windows.h>
#include <map>
#include <vector>

#include "connection.h"
#include "chat_message.h"

class CServer
{
public:
	static CServer* Get();
	
	bool Start(int port, bool isPublic = false);
	void Stop();
	void Run();

private:
	CServer();

	void AcceptConnection(SOCKET socket);
	void KillConnection(int id);

	void SendHelloMessage(int id);

	bool ProcessPacket(int id, PacketType _packetType);
	bool Send(int id, char* data, int totalBytes);
	bool Recieve(int id, char* data, int totalBytes);
	bool SendInt32(int id, int32_t data);
	bool GetInt32(int id, int32_t &data);
	bool SendPacketType(int id, PacketType data);
	bool GetPacketType(int id, PacketType &data);
	void SendString(int id, std::string &data);
	bool GetString(int id, std::string &data);

	static void ClientHandlerThread(int id);
	static void PacketSenderThread();

private:
	static CServer* s_singleton;

	bool m_isRunning;

	SOCKET m_socket;
	SOCKADDR_IN m_addr;
	int m_addrlen;

	std::map<unsigned int, std::shared_ptr<Connection>> m_pConnections;
	std::vector<unsigned int> m_unusedConnectionsIds;

	HANDLE m_hPacketSenderThread;
	std::recursive_mutex m_connectionsMutex;
};

#endif