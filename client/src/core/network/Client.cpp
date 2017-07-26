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
		g_pClient->Recieve((char*)&packetType, sizeof(PacketType));

		if (!g_pClient->ProcessPacket(packetType))
			break;
	}

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

		string hiMessage = "Hi Server!";

		int bufferLength = hiMessage.size();
		PacketType packetType = PT_CHAT_MESSAGE;
		Send((char*)&packetType, sizeof(PacketType));
		Send((char*)&bufferLength, sizeof(int));
		send(m_Connection, hiMessage.c_str(), bufferLength, NULL);

		return true;
	}

	int Client::Send(char* buffer, int bufferLength)
	{
		int result = send(m_Connection, buffer, bufferLength, NULL);
		if (result < 0)
		{
			return 0;
		}

		return result;
	}

	int Client::Recieve(char* buffer, int bufferLength)
	{
		int result = recv(m_Connection, buffer, bufferLength, NULL);
		if (result < 0)
		{
			return 0;
		}

		return result;
	}

	bool Client::ProcessPacket(PacketType packetType)
	{
		switch (packetType)
		{
			case PT_CHAT_MESSAGE:
			{
				int bufferLength;
				Recieve((char*)&bufferLength, sizeof(int));

				char* buffer = new char[bufferLength + 1];
				buffer[bufferLength] = '\0';
				Recieve(buffer, bufferLength);

				delete[] buffer;
				break;
			}
			default:
				OutputDebugString("Unrecognized packet type");
				break;
		}

		return true;
	}
}
