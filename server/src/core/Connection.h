#ifndef CONNECTION_H
#define CONNECTION_H

#include "PacketManager.h"

namespace NixieServer
{
	class Connection
	{
	public:
		Connection(SOCKET socket);

	public:
		SOCKET m_Socket;
		PacketManager m_PacketManager;
		bool m_IsActive;
	};
}

#endif // !CONNECTION_H