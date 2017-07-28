#ifndef PACKETMANAGER_H

#include "Packet.h"

using std::queue;
using std::mutex;
using std::lock_guard;
using std::swap;

namespace NixieServer
{
	class PacketManager
	{
	public:
		PacketManager();
		~PacketManager();

		bool HasPendingPackets();
		void Append(Packet packet);
		Packet Retrieve();
		void Clear();

	private:
		queue<Packet> m_PacketsQueue;
		mutex m_PacketsMutex;
	};
}

#endif // !PACKETMANAGER_H