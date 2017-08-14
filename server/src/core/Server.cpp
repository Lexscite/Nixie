#include "Server.h"

CServer::CServer()
{
	m_addrlen = sizeof(m_addr);
	m_nUnusedConnections = 0;
	m_isRunning = false;
	m_hPacketSenderThread = 0;
}

CServer* CServer::s_singleton;

CServer* CServer::GetSingleton()
{
	if (s_singleton == nullptr)
		s_singleton = new CServer;

	return s_singleton;
}

bool CServer::Start(int port, bool isPublic)
{
	WSADATA wsaData;
	WORD dllVersion = MAKEWORD(2, 2);

	if (WSAStartup(dllVersion, &wsaData) != 0)
	{
		std::cout << "WinSock2 startup failed." << std::endl;
		return false;
	}

	if (isPublic)
		m_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	else
		m_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	m_addr.sin_port = htons(port);
	m_addr.sin_family = AF_INET;

	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (bind(m_socket, (SOCKADDR*)&m_addr, m_addrlen) == SOCKET_ERROR)
	{
		std::cout << "Failed to bind the address. Winsock Error: " << WSAGetLastError() << std::endl;
		return false;
	}

	if (listen(m_socket, SOMAXCONN) == SOCKET_ERROR)
	{
		std::cout << "Failed to listen on listening socket. Winsock Error: " << WSAGetLastError() << std::endl;
		return false;
	}

	m_hPacketSenderThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)PacketSenderThread, NULL, NULL, NULL);

	m_isRunning = true;
	return true;
}

void CServer::Stop()
{
	m_isRunning = false;
	TerminateThread(m_hPacketSenderThread, 0);

	for (int i = 0; i < (int)m_pConnections.size(); i++)
	{
		TerminateThread(m_pConnections[i]->m_hThread, 0);
	}
}

void CServer::Run()
{
	while (m_isRunning)
	{
		SOCKET newConnectionSocket = INVALID_SOCKET;
		newConnectionSocket = accept(m_socket, (SOCKADDR*)&m_addr, &m_addrlen);
		if (newConnectionSocket == INVALID_SOCKET)
		{
			std::cout << "Failed to accept the client's connection." << std::endl;
			Stop();
			return;
		}
		else
		{
			std::lock_guard<std::mutex> lock(m_connectionsMutex);

			int newConnectionId = (int)m_pConnections.size();
			if (m_nUnusedConnections > 0)
			{
				for (int i = 0; i < (int)m_pConnections.size(); i++)
				{
					if (m_pConnections[i]->m_isActive == false)
					{
						m_pConnections[i]->m_socket = newConnectionSocket;
						m_pConnections[i]->m_isActive = true;
						newConnectionId = i;

						m_nUnusedConnections--;
						break;
					}
				}
			}
			else
			{
				std::shared_ptr<CConnection> newConnection(new CConnection(newConnectionSocket));

				std::cout << "Client connected (ID: " << newConnectionId << ")." << std::endl;
				newConnection->m_hThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandlerThread, (LPVOID)(INT_PTR)newConnectionId, NULL, NULL);
				m_pConnections.push_back(newConnection);
			}

			if (!SendPacketType(newConnectionId, PacketType::ChatMessage))
				std::cout << "Failed to send welcome message PK type." << std::endl;
			SendString(newConnectionId, std::string("Hi Client!"));
		}
	}
}

void CServer::KillConnection(int id)
{
	std::lock_guard<std::mutex> lock(m_connectionsMutex);

	if (!m_pConnections[id]->m_isActive)
		return;

	m_pConnections[id]->m_packetManager.Clear();
	m_pConnections[id]->m_isActive = false;
	closesocket(m_pConnections[id]->m_socket);

	if (id == ((int)m_pConnections.size() - 1))
	{
		m_pConnections.pop_back();

		if (m_pConnections.size() > 0)
		{
			for (int i = (int)m_pConnections.size() - 1; i >= 0 && (int)m_pConnections.size() > 0; i--)
			{
				if (m_pConnections[i]->m_isActive)
					break;

				m_pConnections.pop_back();
				m_nUnusedConnections--;
			}
		}
	}
	else
		m_nUnusedConnections++;
}

bool CServer::Send(int id, char* data, int totalBytes)
{
	int sentBytes = 0;
	while (sentBytes < totalBytes)
	{
		int result = send(m_pConnections[id]->m_socket, data + sentBytes, totalBytes - sentBytes, NULL);
		if (result == SOCKET_ERROR)
			return false;
		else if (result == 0)
		{
			int iError = WSAGetLastError();
			if (iError == WSAEWOULDBLOCK)
				std::cout << "WS function send failed with error: WSAEWOULDBLOCK\n" << std::endl;
			else
				std::cout << "WS function send failed with error: %ld\n" << iError << std::endl;
			return false;
		}
		sentBytes += result;
	}

	return true;
}

bool CServer::Recieve(int id, char* data, int totalBytes)
{
	int recievedBytes = 0;
	while (recievedBytes < totalBytes)
	{
		int result = recv(m_pConnections[id]->m_socket, data + recievedBytes, totalBytes - recievedBytes, NULL);
		if (result == SOCKET_ERROR)
			return false;
		else if (result == 0)
		{
			int iError = WSAGetLastError();
			if (iError == WSAEWOULDBLOCK)
				std::cout << "WS function send failed with error: WSAEWOULDBLOCK\n" << std::endl;
			else
				std::cout << "WS function send failed with error: %ld\n" << iError << std::endl;
			return false;
		}

		recievedBytes += result;
	}

	return true;
}

bool CServer::SendInt32(int id, int32_t data)
{
	data = htonl(data);
	if (!Send(id, (char*)&data, sizeof(int32_t)))
		return false;

	return true;
}

bool CServer::GetInt32(int id, int32_t &data)
{
	if (!Recieve(id, (char*)&data, sizeof(int32_t)))
		return false;
	data = ntohl(data);

	return true;
}

bool CServer::SendPacketType(int id, PacketType data)
{
	if (!SendInt32(id, (int32_t)data))
		return false;

	return true;
}

bool CServer::GetPacketType(int id, PacketType &data)
{
	int32_t dataInt;
	if (!GetInt32(id, dataInt))
		return false;
	data = (PacketType)dataInt;

	return true;
}

void CServer::SendString(int id, std::string &data)
{
	CChatMessage message(data);
	m_pConnections[id]->m_packetManager.Append(message.ToPacket());
}

bool CServer::GetString(int id, std::string &data)
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

bool CServer::ProcessPacket(int id, PacketType _packetType)
{
	switch (_packetType)
	{
	case PacketType::LoginData:
	{
		std::cout << "Client sent a PK login data:" << std::endl;
		break;
	}
	case PacketType::ChatMessage:
	{
		std::string message;
		if (!GetString(id, message))
			return false;

		for (int i = 0; i < (int)m_pConnections.size(); i++)
		{
			if (!m_pConnections[i]->m_isActive)
				continue;

			if (i == id)
				continue;

			PacketType packetType = PacketType::ChatMessage;
			if (!SendPacketType(i, packetType))
				std::cerr << "Failed to send packet type" << std::endl;

			SendString(i, message);
		}

		std::cout << "Processed chat message PK from the client (ID: " << id << "): " << message << std::endl;
		break;
	}
	default:
		std::cout << "Unrecognized packet: " << (int32_t)_packetType << std::endl;
		break;
	}

	return true;
}

void CServer::ClientHandlerThread(int id)
{
	PacketType packetType;
	while (true)
	{
		if (!CServer::GetSingleton()->GetPacketType(id, packetType))
			break;

		if (!CServer::GetSingleton()->ProcessPacket(id, packetType))
			break;
	}

	CServer::GetSingleton()->KillConnection(id);
	std::cout << "Lost connection to the client (ID: " << id << ")." << std::endl;
}

void CServer::PacketSenderThread()
{
	while (true)
	{
		for (int i = 0; i < (int)CServer::GetSingleton()->m_pConnections.size(); i++)
		{
			if (CServer::GetSingleton()->m_pConnections[i]->m_packetManager.HasPendingPackets())
			{
				CPacket pendingPacket = CServer::GetSingleton()->m_pConnections[i]->m_packetManager.Retrieve();
				if (!CServer::GetSingleton()->Send(i, pendingPacket.m_buffer, pendingPacket.m_size))
					std::cout << "Failed to send packet to client (ID: " << i << ")" << std::endl;

				delete pendingPacket.m_buffer;
			}
		}
	}
}