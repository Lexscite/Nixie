#include "Client.h"

namespace NixieClient
{
	Client::Client()
	{
	}

	Client::~Client()
	{
	}

	bool Client::Connect()
	{
		m_DllVersion = MAKEWORD(2, 2);

		if (WSAStartup(m_DllVersion, &m_WSAData) != 0)
		{
			MessageBox(NULL, "WinSock2 startup failed", "Error", MB_OK | MB_ICONERROR);
			return false;
		}

		int addressLen = sizeof(m_Address);
		m_Address.sin_addr.s_addr = inet_addr("127.0.0.1");
		m_Address.sin_port = htons(1111);
		m_Address.sin_family = AF_INET;

		SOCKET connection = socket(AF_INET, SOCK_STREAM, NULL);
		if (connect(connection, (SOCKADDR*)&m_Address, addressLen) != 0)
		{
			MessageBox(NULL, "Failed to connect.", "Error", MB_OK | MB_ICONERROR);
			return false;
		}

		return true;
	}
}
