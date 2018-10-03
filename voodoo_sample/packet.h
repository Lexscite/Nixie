#ifndef PACKET_H_
#define PACKET_H_

#pragma comment(lib,"ws2_32.lib")

namespace voodoo
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