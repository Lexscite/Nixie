#include "Connection.h"

Connection::Connection(int id, SOCKET socket)
{
	m_id = id;
	m_socket = socket;
	m_isActive = true;
}

void Connection::Kill()
{
	if (!m_isActive)
		return;

	m_packetManager.Clear();
	m_isActive = false;
}