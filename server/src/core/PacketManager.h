#ifndef __PACKETMANAGER_H__
#define __PACKETMANAGER_H__

#include "Packet.h"

using std::queue;
using std::mutex;
using std::lock_guard;
using std::swap;

class CPacketManager
{
public:
	CPacketManager();

	bool HasPendingPackets();
	void Append(CPacket packet);
	CPacket Retrieve();
	void Clear();

private:
	queue<CPacket> m_packetsQueue;
	mutex m_packetsMutex;
};

#endif