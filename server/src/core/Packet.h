#ifndef PACKET_H
#define PACKET_H

#include <iostream>
#include <WinSock2.h>
#include <string>

#pragma comment(lib,"ws2_32.lib")

using namespace std;

enum class PacketType
{
	PT_LOGIN_DATA,
	PT_CHAT_MESSAGE,
};

class Packet
{
public:
	Packet();
	~Packet();
};

#endif // !PACKET_H