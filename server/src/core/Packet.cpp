#include "Packet.h"

namespace NixieServer
{
	Packet::Packet()
	{
	}

	Packet::Packet(char* buffer, int size)
	{
		m_Buffer = buffer;
		m_Size = size;
	}

	Packet::Packet(const Packet &packet)
	{
		m_Size = packet.m_Size;
		m_Buffer = new char[m_Size];
		memcpy(m_Buffer, packet.m_Buffer, m_Size);
	}

	Packet::~Packet()
	{
	}
}