#include "PacketManager.h"

CPacketManager::CPacketManager()
{
}

CPacketManager::~CPacketManager()
{
}

bool CPacketManager::HasPendingPackets()
{
	return (m_packetsQueue.size() > 0);
}

void CPacketManager::Append(CPacket packet)
{
	lock_guard<mutex> lock(m_packetsMutex);

	m_packetsQueue.push(packet);
}

CPacket CPacketManager::Retrieve()
{
	lock_guard<mutex> lock(m_packetsMutex);

	CPacket frontPacket = m_packetsQueue.front();
	m_packetsQueue.pop();

	return frontPacket;
}

void CPacketManager::Clear()
{
	lock_guard<mutex> lock(m_packetsMutex);

	queue<CPacket> empty;
	swap(m_packetsQueue, empty);
}