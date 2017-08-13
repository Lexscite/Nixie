#ifndef PACKET_H
#define PACKET_H

#include <windows.h>
#include <string>

#pragma comment(lib,"ws2_32.lib")

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

#endif
