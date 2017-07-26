#include "Client.h"

namespace
{
	NixieClient::Client* g_pClient = nullptr;
}

void ClientThread()
{
	PacketType packetType;

	while (true)
	{
		if (!g_pClient->GetPacketType(packetType))
			break;

		if (!g_pClient->ProcessPacket(packetType))
			break;
	}

	MessageBox(NULL, "Lost connection to the server", "Network Error", MB_OK | MB_ICONERROR);
	closesocket(g_pClient->m_Connection);
}

namespace NixieClient
{
	Client::Client()
	{
		g_pClient = this;
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

		m_Connection = socket(AF_INET, SOCK_STREAM, NULL);
		if (connect(m_Connection, (SOCKADDR*)&m_Address, addressLen) != 0)
		{
			MessageBox(NULL, "Failed to connect.", "Error", MB_OK | MB_ICONERROR);
			return false;
		}

		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientThread, NULL, NULL, NULL);

		if (!SendPacketType(PT_CHAT_MESSAGE))
			MessageBox(NULL, "Failed to send TEST packet type", "Network Error", MB_OK | MB_ICONERROR);

		string message = string("Hi Server!");

		if (!SendString(message))
			MessageBox(NULL, "Failed to send TEST string", "Network Error", MB_OK | MB_ICONERROR);

		SendPacketType(PT_LOGIN_DATA);

		return true;
	}

	int Client::Send(char* buffer, int bufferLength)
	{
		return send(m_Connection, buffer, bufferLength, NULL);
	}

	int Client::Recieve(char* buffer, int bufferLength)
	{
		return recv(m_Connection, buffer, bufferLength, NULL);
	}

	bool Client::SendInt(int data)
	{
		if (Send((char*)&data, sizeof(int)) == SOCKET_ERROR)
			return false;
		
		return true;
	}

	bool Client::GetInt(int &data)
	{
		if (Recieve((char*)&data, sizeof(int)) == SOCKET_ERROR)
			return false;
		
		return true;
	}

	bool Client::SendPacketType(PacketType data)
	{
		if (Send((char*)&data, sizeof(PacketType)) == SOCKET_ERROR)
			return false;
		
		return true;
	}

	bool Client::GetPacketType(PacketType &data)
	{
		if (Recieve((char*)&data, sizeof(PacketType)) == SOCKET_ERROR)
			return false;
		
		return true;
	}

	bool Client::SendString(string &data)
	{
		int bufferLength = data.size();

		if (!SendInt(bufferLength))
			return false;

		if (Send((char*)data.c_str(), bufferLength) == SOCKET_ERROR)
			return false;

		return true;
	}

	bool Client::GetString(string &data)
	{
		int bufferLength;

		if (!GetInt(bufferLength))
			return false;

		char* buffer = new char[bufferLength + 1];
		buffer[bufferLength] = '\0';

		int result = Recieve(buffer, bufferLength);
		data = buffer;
		delete[] buffer;
		if (result == SOCKET_ERROR)
			return false;

		return true;
	}

	bool Client::ProcessPacket(PacketType packetType)
	{
		switch (packetType)
		{
			case PT_LOGIN_DATA:
			{
				break;
			}
			case PT_CHAT_MESSAGE:
			{
				string message;
				if (!GetString(message))
					return false;

				break;
			}
			default:
				OutputDebugString("Unrecognized packet type");
				break;
		}

		return true;
	}
}