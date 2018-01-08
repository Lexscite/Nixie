#ifndef PACKET_H
#define PACKET_H

#pragma once

#include <windows.h>
#include <string>

#pragma comment(lib,"ws2_32.lib")

namespace Nixie
{
	enum class PacketType
	{
		HelloMessage,
	};

	class Packet
	{
	public:
		Packet();
		~Packet();
	};
}

#endif