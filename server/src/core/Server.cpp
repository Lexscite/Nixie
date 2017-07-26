#include "Server.h"

namespace
{
	NixieServer::Server* g_pServer = nullptr;
}

void HandleClientThread(int id)
{
	PacketType packetType;

	while (true)
	{ 
		g_pServer->Recieve((char*)&packetType, sizeof(PacketType), id);

		if (!g_pServer->ProcessPacket(id, packetType))
			break;
	}

	closesocket(g_pServer->m_Connections[id]);
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
			cout << "Failed to bind the listening socket." << endl;
			return false;
		}

		if (listen(m_SocketListen, SOMAXCONN) != 0)
		{
			cout << "Failed to listen to the socket." << endl;
			return false;
		}

		SOCKET newConnection;
		for (int i = 0; i < ARRAYSIZE(m_Connections); i++)
		{
			newConnection = accept(m_SocketListen, (SOCKADDR*)&m_Address, &addressLen);
			if (newConnection == 0)
			{
				cout << "Failed to accept the client's connection." << endl;
				return false;
			}

			cout << "Client connected." << endl;

			m_Connections[i] = newConnection;
			m_ConnectionCounter++;

			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)HandleClientThread, (LPVOID)(i), NULL, NULL);
		}

		return true;
	}

	int Server::Send(char* buffer, int length, int id)
	{
		int result = send(m_Connections[id], buffer, length, NULL);
		if (result < 0)
		{
			cout << "Failed to send data." << endl;
			return 0;
		}

		return result;
	}

	int Server::Recieve(char* buffer, int length, int id)
	{
		int result = recv(m_Connections[id], buffer, length, NULL);
		if (result < 0)
		{
			cout << "Failed to recieve data." << endl;
			return 0;
		}

		return result;
	}

	bool Server::ProcessPacket(int id, PacketType packetType)
	{
		switch (packetType)
		{
			case PT_LOGIN_DATA:
			{
				cout << "Client sent a PK login data:" << endl;
				break;
			}
			case PT_CHAT_MESSAGE:
			{
				int bufferLength;
				Recieve((char*)&bufferLength, sizeof(int), id);

				char* buffer = new char[bufferLength];
				Recieve(buffer, bufferLength, id);

				cout << "Client sent a PK chat message: " << buffer << endl;

				for (int i = 0; i < m_ConnectionCounter; i++)
				{
					if (i == id)
						continue;

					PacketType responsePacketType = PT_CHAT_MESSAGE;
					Send((char*)&responsePacketType, sizeof(PacketType), i);

					Send((char*)&bufferLength, sizeof(int), i);
					Send(buffer, bufferLength, i);
				}

				delete[] buffer;
				break;
			}
			default:
				cout << "Unrecognized packet: " << packetType << endl;
				break;
		}

		return true;
	}
}