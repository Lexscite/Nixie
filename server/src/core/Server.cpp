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
			string errorMessage = "Failed to bind the address. Winsock Error: " + std::to_string(WSAGetLastError()) + ".";
			cout << errorMessage.c_str() << endl;
			return false;
		}

		if (listen(m_ListeningSocket, SOMAXCONN) == SOCKET_ERROR)
		{
			string errorMessage = "Failed to listen on listening socket. Winsock Error: " + std::to_string(WSAGetLastError()) + ".";
			cout << errorMessage.c_str() << endl;
			return false;
		}

		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)PacketSenderThread, NULL, NULL, NULL);

		return true;
	}

	bool Server::Run()
	{
		SOCKET newSocket;
		newSocket = accept(m_ListeningSocket, (SOCKADDR*)&m_Address, &m_AddressSize);
		if (newSocket == 0)
		{
			cout << "Failed to accept the client's connection." << endl;
			return false;
		}

		m_Connections[m_ConnectionCounter].socket = newSocket;

		cout << "Client connected (ID: " << m_ConnectionCounter << ")." << endl;

		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandlerThread, (LPVOID)(m_ConnectionCounter), NULL, NULL);

		if (!SendPacketType(m_ConnectionCounter, PacketType::ChatMessage))
			cout << "Failed to send welcome message PK type." << endl;
		SendString(m_ConnectionCounter, string("Hi Client!"));

		m_ConnectionCounter++;

		return true;
	}

	bool Server::Send(int id, char* data, int totalBytes)
	{
		int sentBytes = 0;
		while (sentBytes < totalBytes)
		{
			int result = send(m_Connections[id].socket, data + sentBytes, totalBytes - sentBytes, NULL);
			if (result == SOCKET_ERROR)
				return false;
			else if (result == 0)
			{
				int iError = WSAGetLastError();
				if (iError == WSAEWOULDBLOCK)
					cout << "WS function send failed with error: WSAEWOULDBLOCK\n" << endl;
				else
					cout << "WS function send failed with error: %ld\n" << iError << endl;
				return false;
			}
			sentBytes += result;
		}

		return true;
	}

	bool Server::Recieve(int id, char* data, int totalBytes)
	{
		int recievedBytes = 0;
		while (recievedBytes < totalBytes)
		{
			int result = recv(m_Connections[id].socket, data + recievedBytes, totalBytes - recievedBytes, NULL);
			if (result == SOCKET_ERROR)
				return false;
			else if (result == 0)
			{
				int iError = WSAGetLastError();
				if (iError == WSAEWOULDBLOCK)
					cout << "WS function send failed with error: WSAEWOULDBLOCK\n" << endl;
				else
					cout << "WS function send failed with error: %ld\n" << iError << endl;
				return false;
			}

			recievedBytes += result;
		}

		return true;
	}

	bool Server::SendInt32(int id, int32_t data)
	{
		data = htonl(data);
		if (!Send(id, (char*)&data, sizeof(int32_t)))
			return false;

		return true;
	}

	bool Server::GetInt32(int id, int32_t &data)
	{
		if (!Recieve(id, (char*)&data, sizeof(int32_t)))
			return false;
		data = ntohl(data);

		return true;
	}

	bool Server::SendPacketType(int id, PacketType data)
	{
		if (!SendInt32(id, (int32_t)data))
			return false;

		return true;
	}

	bool Server::GetPacketType(int id, PacketType &data)
	{
		int32_t dataInt;
		if (!GetInt32(id, dataInt))
			return false;
		data = (PacketType)dataInt;

		return true;
	}

	void Server::SendString(int id, string &data)
	{
		ChatMessage message(data);
		m_Connections[id].packetManager.Append(message.ToPacket());
	}

	bool Server::GetString(int id, string &data)
	{
		int32_t bufferLength;

		if (!GetInt32(id, bufferLength))
			return false;

		char* buffer = new char[bufferLength + 1];
		buffer[bufferLength] = '\0';

		if (!Recieve(id, buffer, bufferLength))
		{
			delete[] buffer;
			return false;
		}

		data = buffer;
		delete[] buffer;

		return true;
	}

	bool Server::ProcessPacket(int id, PacketType _packetType)
	{
		switch (_packetType)
		{
			case PacketType::LoginData:
			{
				cout << "Client sent a PK login data:" << endl;
				break;
			}
			case PacketType::ChatMessage:
			{
				string message;
				if (!GetString(id, message))
					return false;

				for (int i = 0; i < ARRAYSIZE(m_Connections); i++)
				{
					if (i != id)
						continue;

					SendString(i, message);
				}

				cout << "Processed chat message PK from the client (ID: " << id << "): " << message.c_str() << endl;
				break;
			}
			default:
				cout << "Unrecognized packet: " << (int32_t)_packetType << endl;
				break;
		}

		return true;
	}

	void Server::ClientHandlerThread(int id)
	{
		PacketType packetType;
		while (true)
		{
			if (!g_pServer->GetPacketType(id, packetType))
				break;

			if (!g_pServer->ProcessPacket(id, packetType))
				break;
		}

		cout << "Lost connection to the client (ID: " << id << ")." << endl;
		closesocket(g_pServer->m_Connections[id].socket);
	}

	void Server::PacketSenderThread()
	{
		while (true)
		{
			for (int i = 0; i < g_pServer->m_ConnectionCounter; i++)
			{
				if (g_pServer->m_Connections[i].packetManager.HasPendingPackets())
				{
					Packet pendingPacket = g_pServer->m_Connections[i].packetManager.Retrieve();
					if (!g_pServer->Send(i, pendingPacket.m_Buffer, pendingPacket.m_Size))
					{
						cout << "Failed to send packet to client (ID: " << i << ")" << endl;
					}
					delete pendingPacket.m_Buffer;
				}
			}
		}
	}
}