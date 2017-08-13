#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include "PacketManager.h"

class CConnection
{
public:
	CConnection(SOCKET socket);

public:
	SOCKET m_socket;
	CPacketManager m_packetManager;
	bool m_isActive;
	HANDLE m_hThread;
};

#endif