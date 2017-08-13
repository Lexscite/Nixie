#include "Connection.h"

CConnection::CConnection(SOCKET socket)
{
	m_socket = socket;
	m_isActive = true;
}