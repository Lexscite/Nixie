#include "packet_manager.h"

CPacketManager::CPacketManager() {}

bool CPacketManager::HasPendingPackets()
{
	std::lock_guard<std::recursive_mutex> lockGuard(m_packetsMutex);

	return m_packetsQueue.size() > 0;
}

void CPacketManager::Append(CPacket packet)
{
	std::lock_guard<std::recursive_mutex> lockGuard(m_packetsMutex);

	m_packetsQueue.push(packet);
}

CPacket CPacketManager::Retrieve()
{
	std::lock_guard<std::recursive_mutex> lockGuard(m_packetsMutex);

	CPacket frontPacket = m_packetsQueue.front();
	m_packetsQueue.pop();

	return frontPacket;
}

void CPacketManager::Clear()
{
	std::lock_guard<std::recursive_mutex> lockGuard(m_packetsMutex);

	std::queue<CPacket> empty;
	std::swap(m_packetsQueue, empty);
}