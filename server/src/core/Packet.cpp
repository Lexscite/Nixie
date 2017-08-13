#include "Packet.h"

CPacket::CPacket()
{
}

CPacket::~CPacket()
{
}

CPacket::CPacket(char* buffer, int size)
{
	m_buffer = buffer;
	m_size = size;
}

CPacket::CPacket(const CPacket &packet)
{
	m_size = packet.m_size;
	m_buffer = new char[m_size];
	memcpy(m_buffer, packet.m_buffer, m_size);
}