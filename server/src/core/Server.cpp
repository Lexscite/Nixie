#include "Server.h"

namespace
{
	NixieServer::Server* g_pServer = nullptr;
}

int HandleClientThread(int index)
{
	char buffer[256];
	while (true)
	{
		recv(g_pServer->m_Connections[index], buffer, sizeof(buffer), NULL);
		for (int i = 0; i < g_pServer->m_ConnectionCounter; i++)
		{
			if (i == index)
				continue;

			send(g_pServer->m_Connections[i], buffer, sizeof(buffer), NULL);
		}
	}
}

namespace NixieServer
{
	Server::Server()
	{
		g_pServer = this;
	}

	Server::~Server()
	{
	}

	bool Server::Start()
	{
		m_DllVersion = MAKEWORD(2, 2);

		if (WSAStartup(m_DllVersion, &m_WSAData) != 0)
		{
			MessageBox(NULL, "WinSock2 startup failed", "Error", MB_OK | MB_ICONERROR);
			exit(1);
		}

		int addressLen = sizeof(m_Address);
		m_Address.sin_addr.s_addr = inet_addr("127.0.0.1");
		m_Address.sin_port = htons(1111);
		m_Address.sin_family = AF_INET;

		m_SocketListen = socket(AF_INET, SOCK_STREAM, NULL);
		if (bind(m_SocketListen, (SOCKADDR*)&m_Address, sizeof(m_Address)) != 0)
		{
			std::cout << "Failed to bind the listening socket." << std::endl;
			return false;
		}

		if (listen(m_SocketListen, SOMAXCONN) != 0)
		{
			std::cout << "Failed to listen to the socket." << std::endl;
			return false;
		}

		SOCKET newConnection;
		for (int i = 0; i < ARRAYSIZE(m_Connections); i++)
		{
			newConnection = accept(m_SocketListen, (SOCKADDR*)&m_Address, &addressLen);
			if (newConnection == 0)
			{
				std::cout << "Failed to accept the client's connection." << std::endl;
				return false;
			}

			std::cout << "Client connected." << std::endl;

			char MOTD[256] = "Welcome! This is the message of the day.";
			send(newConnection, MOTD, sizeof(MOTD), NULL);

			m_Connections[i] = newConnection;
			m_ConnectionCounter++;

			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)HandleClientThread, (LPVOID)(i), NULL, NULL);
		}

		return true;
	}
}