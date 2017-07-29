#ifndef PACKET_H
#define PACKET_H

#include <windows.h>
#include <string>

#pragma comment(lib,"ws2_32.lib")

namespace NXNetwork
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
	};
}

#endif // !PACKET_H
