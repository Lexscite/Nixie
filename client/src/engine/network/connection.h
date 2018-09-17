#ifndef NIXIE_CONNECTION_H_
#define NIXIE_CONNECTION_H_

#pragma once

#include "packet.h"

namespace nixie
{
	class Connection
	{
	public:
		bool Establish(std::string ip, int port);
		void Release();
		bool Kill();

		bool SendPacketType(PacketType data);
		bool SendString(std::string &data);

		static Connection* GetSingleton();

	private:
		Connection();

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

		static Connection* s_singleton;
	};
}

#endif