#ifndef PACKETMANAGER_H

#include "ChatMessage.h"

using std::queue;
using std::mutex;
using std::lock_guard;

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
	private:
		queue<Packet> m_PacketsQueue;
		mutex m_PacketsMutex;
	};
}

#endif // !PACKETMANAGER_H