#ifndef __PACKET_H__
#define __PACKET_H__

#include <iostream>
#include <string>
#include <queue>
#include <mutex>
#include <windows.h>

#pragma comment(lib,"ws2_32.lib")

using std::string;

enum class PacketType
{
	LoginData,
	ChatMessage,
};

class CPacket
{
public:
	CPacket();
	~CPacket();

	CPacket(char* buffer, int size);
	CPacket(const CPacket &packet);

public:
	char* m_buffer;
	int m_size;
};

#endif