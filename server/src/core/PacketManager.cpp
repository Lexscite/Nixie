#include "PacketManager.h"

namespace NixieServer
{
	PacketManager::PacketManager()
	{
	}

	PacketManager::~PacketManager()
	{
	}

	bool PacketManager::HasPendingPackets()
	{
		return (m_PacketsQueue.size() > 0);
	}

	void PacketManager::Append(Packet packet)
	{
		lock_guard<mutex> lock(m_PacketsMutex);

		m_PacketsQueue.push(packet);
	}

	Packet PacketManager::Retrieve()
	{
		lock_guard<mutex> lock(m_PacketsMutex);

		Packet frontPacket = m_PacketsQueue.front();
		m_PacketsQueue.pop();

		return frontPacket;
	}

	void PacketManager::Clear()
	{
		lock_guard<mutex> lock(m_PacketsMutex);
		queue<Packet> empty;
		swap(m_PacketsQueue, empty);
	}
}