#include "Server.h"

namespace NixieServer
{
	Server::Server()
	{
		m_NumMaxClients = 10;
		m_NumMaxClients = 0;
	}

	Server::~Server()
	{
	}

	bool Server::Start(int port)
	{
		if (WSAStartup(MAKEWORD(2, 2), &m_SocketVersion) != NO_ERROR)
		{
			cout << "(E) WSA startup failed." << endl;
			return false;
		}
		cout << "(OK) WSA started." << endl;

		m_Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (m_Socket == INVALID_SOCKET)
		{
			cout << "(E) Socket is invalid." << endl;
			WSACleanup();
			return false;
		}
		cout << "(OK) Socket created." << endl;

		m_SocketAddress.sin_family = AF_INET;
		m_SocketAddress.sin_addr.s_addr = htonl(INADDR_ANY);
		m_SocketAddress.sin_port = htons(port);

		if (bind(m_Socket, (LPSOCKADDR)&m_SocketAddress, sizeof(m_SocketAddress)) != NO_ERROR)
		{
			cout << "(E) Socket binding failed." << endl;
			return false;
		}
		cout << "(OK) Socket is binded." << endl;

		while (true)
		{
			for (int i = 0; i < m_NumMaxClients; i++)
			{
				if (m_NumCurrentClients < m_NumMaxClients)
				{
					int clientSocketInfoLength = sizeof(m_ClientSocketAddress);

					m_ClientSockets[m_NumCurrentClients] = accept(m_Socket, (sockaddr*)&m_ClientSocketAddress, &clientSocketInfoLength);
					if (m_ClientSockets[m_NumCurrentClients] == INVALID_SOCKET)
					{
						cout << "(E) Invalid client socket." << endl;
						return false;
					}

					cout << "(OK) Client has jouned the server (IP: " << m_ClientSocketAddress.sin_addr.s_addr << ")." << endl;

					m_NumCurrentClients++;

					continue;
				}
				else
				{
					break;
				}
			}
		}

		return true;
	}

	int Server::Send(char* data, int length, int clientId)
	{
		int messageLength = send(m_ClientSockets[clientId], data, length, NULL);
		if (messageLength < 0)
		{
			printf("Cannot send data!");
			return 0;
		}

		return messageLength;
	}

	void Server::SendToAll(char* data, int length, int clientId)
	{
		for (int i = 0; i < m_NumCurrentClients; i++)
		{
			Send(data, length, i);
		}
	}

	int Server::Recieve(char* data, int length, int clientId)
	{
		int messageLength = recv(m_ClientSockets[clientId], data, length, NULL);
		if (messageLength < 0)
		{
			printf("Cannot recieve data!");
			return 0;
		}

		return messageLength;
	}

	bool Server::CloseSocket()
	{
		closesocket(m_Socket);
		WSACleanup();

		return true;
	}
}