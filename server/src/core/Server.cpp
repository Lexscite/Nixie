#include "Server.h"

static NixieServer::Server* g_pServer;

namespace NixieServer
{
	Server::Server()
	{
		g_pServer = this;
		m_AddressSize = sizeof(m_Address);
		m_ConnectionCounter = 0;
	}

	Server::~Server()
	{
	}

	bool Server::Start(int port, bool broadcastPublically)
	{
		WSADATA wsaData;
		WORD dllVersion = MAKEWORD(2, 2);

		if (WSAStartup(dllVersion, &wsaData) != 0)
		{
			cout << "WinSock2 startup failed." << endl;
			return false;
		}

		if (broadcastPublically)
			m_Address.sin_addr.s_addr = htonl(INADDR_ANY);
		else
			m_Address.sin_addr.s_addr = inet_addr("127.0.0.1");

		m_Address.sin_port = htons(port);
		m_Address.sin_family = AF_INET;

		m_ListeningSocket = socket(AF_INET, SOCK_STREAM, NULL);

		if (bind(m_ListeningSocket, (SOCKADDR*)&m_Address, m_AddressSize) == SOCKET_ERROR)
		{
			string errorMessage = "Failed to bind the address. Winsock Error: " + to_string(WSAGetLastError()) + ".";
			cout << errorMessage.c_str() << endl;
			return false;
		}

		if (listen(m_ListeningSocket, SOMAXCONN) == SOCKET_ERROR)
		{
			string errorMessage = "Failed to listen on listening socket. Winsock Error: " + to_string(WSAGetLastError()) + ".";
			cout << errorMessage.c_str() << endl;
			return false;
		}

		return true;
	}

	bool Server::ListenForNewConnection()
	{
		SOCKET newConnection;
		newConnection = accept(m_ListeningSocket, (SOCKADDR*)&m_Address, &m_AddressSize);
		if (newConnection == 0)
		{
			cout << "Failed to accept the client's connection." << endl;
			return false;
		}

		cout << "Client connected." << endl;

		m_Connections[m_ConnectionCounter] = newConnection;

		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Thread, (LPVOID)(m_ConnectionCounter), NULL, NULL);

		if (!SendPacketType(m_ConnectionCounter, PT_CHAT_MESSAGE))
			cout << "Failed to send welcome message PK type." << endl;
		if (!SendString(m_ConnectionCounter, string("Hi Client!")))
			cout << "Failed to send welcome message." << endl;

		m_ConnectionCounter++;

		return true;
	}

	int Server::Send(int id, char* buffer, int length)
	{
		int result = send(m_Connections[id], buffer, length, NULL);
		if (result < 0)
		{
			return 0;
		}

		return result;
	}

	int Server::Recieve(int id, char* buffer, int length)
	{
		int result = recv(m_Connections[id], buffer, length, NULL);
		if (result < 0)
		{
			return 0;
		}

		return result;
	}

	bool Server::SendInt(int id, int data)
	{
		if (Send(id, (char*)&data, sizeof(int)) == SOCKET_ERROR)
			return false;

		return true;
	}

	bool Server::GetInt(int id, int &data)
	{
		if (Recieve(id, (char*)&data, sizeof(int)) == SOCKET_ERROR)
			return false;

		return true;
	}

	bool Server::SendPacketType(int id, PacketType data)
	{
		if (Send(id, (char*)&data, sizeof(PacketType)) == SOCKET_ERROR)
			return false;

		return true;
	}

	bool Server::GetPacketType(int id, PacketType &data)
	{
		if (Recieve(id, (char*)&data, sizeof(PacketType)) == SOCKET_ERROR)
			return false;

		return true;
	}

	bool Server::SendString(int id, string &data)
	{
		int bufferLength = data.size();

		if (!SendInt(id, bufferLength))
			return false;

		if (Send(id, (char*)data.c_str(), bufferLength) == SOCKET_ERROR)
			return false;

		return true;
	}

	bool Server::GetString(int id, string &data)
	{
		int bufferLength;

		if (!GetInt(id, bufferLength))
			return false;

		char* buffer = new char[bufferLength + 1];
		buffer[bufferLength] = '\0';

		int result = Recieve(id, buffer, bufferLength);
		data = buffer;
		delete[] buffer;
		if (result == SOCKET_ERROR)
			return false;

		return true;
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
				string message;
				if (!GetString(id, message))
					return false;

				for (int i = 0; i < ARRAYSIZE(m_Connections); i++)
				{
					if (i == id)
						continue;

					if (!SendPacketType(i, PT_CHAT_MESSAGE))
					{
						cout << "Failed to send PK type from the client (ID: " << id << ")" << endl;
						break;
					}

					if (!SendString(i, message))
					{
						cout << "Failed to send chat message PK from the client (ID: " << id << ")" << endl;
						break;
					}
				}

				cout << "Processed chat message PK from the client (ID: " << id << "): " << message.c_str() << endl;
				break;
			}
			default:
				cout << "Unrecognized packet: " << packetType << endl;
				break;
		}

		return true;
	}

	void Server::Thread(int id)
	{
		PacketType packetType;
		while (true)
		{
			if (!g_pServer->GetPacketType(id, packetType))
				break;

			if (!g_pServer->ProcessPacket(id, packetType))
				break;
		}

		cout << "Lost connection to the client (ID:" << id << ")." << endl;
		closesocket(g_pServer->m_Connections[id]);
	}
}