#ifndef __PACKET_H__
#define __PACKET_H__

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
