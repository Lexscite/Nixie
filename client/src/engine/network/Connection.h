#ifndef __CLIENT_H__
#define __CLIENT_H__

#pragma once

#include "Packet.h"
#include <iostream>

class CConnection
{
public:
	bool Init(std::string ip, int port);
	void Release();
	bool Close();

	bool SendPacketType(PacketType data);
	bool SendString(std::string &data);

	static CConnection* GetSingleton();

private:
	CConnection();

	bool ProcessPacket(PacketType packetType);
	bool Send(char *data, int totalBytes);
	bool Recieve(char *data, int totalBytes);
	bool SendInt32(int32_t data);
	bool GetInt32(int32_t &data);
	bool GetPacketType(PacketType &data);
	bool GetString(std::string &data);

	static void Thread();

private:
	SOCKET m_Socket;
	SOCKADDR_IN m_Address;
	int m_AddressSize;

	static CConnection* s_singleton;
};

#endif