#include "Connection.h"

namespace NixieServer
{
	Connection::Connection(SOCKET socket)
	{
		m_Socket = socket;
		m_IsActive = true;
	}
}