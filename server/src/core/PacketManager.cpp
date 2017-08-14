#include "PacketManager.h"

CPacketManager::CPacketManager() {}

bool CPacketManager::HasPendingPackets()
{
	return (m_packetsQueue.size() > 0);
}

void CPacketManager::Append(CPacket packet)
{
	std::lock_guard<std::mutex> lock(m_packetsMutex);

	m_packetsQueue.push(packet);
}

CPacket CPacketManager::Retrieve()
{
	std::lock_guard<std::mutex> lock(m_packetsMutex);

	CPacket frontPacket = m_packetsQueue.front();
	m_packetsQueue.pop();

	return frontPacket;
}

void CPacketManager::Clear()
{
	std::lock_guard<std::mutex> lock(m_packetsMutex);

	std::queue<CPacket> empty;
	std::swap(m_packetsQueue, empty);
}