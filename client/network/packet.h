#ifndef PACKET_H_
#define PACKET_H_

#pragma once

#pragma comment(lib,"ws2_32.lib")


namespace nixie
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