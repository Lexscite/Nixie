#ifndef PACKET_H
#define PACKET_H

#include <iostream>
#include <string>
#include <queue>
#include <mutex>
#include <windows.h>

#pragma comment(lib,"ws2_32.lib")

using std::string;

namespace NixieServer
{
	enum class PacketType
	{
		LoginData,
		ChatMessage,
	};

	class Packet
	{
	public:
		Packet();
		~Packet();

		Packet(char* buffer, int size);
		Packet(const Packet &packet);

	public:
		char* m_Buffer;
		int m_Size;
	};
}

#endif // !PACKET_H