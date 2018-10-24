#ifndef __PACKETMANAGER_H__
#define __PACKETMANAGER_H__

#pragma once

#include "Packet.h"

class CPacketManager
{
public:
	CPacketManager();

	bool HasPendingPackets();
	void Append(CPacket packet);
	CPacket Retrieve();
	void Clear();

private:
	std::queue<CPacket> m_packetsQueue;
	std::recursive_mutex m_packetsMutex;
};

#endif