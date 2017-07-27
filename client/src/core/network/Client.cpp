#include "Client.h"

static NixieClient::Client* g_pClient;

namespace NixieClient
{
	Client::Client()
	{
		g_pClient = this;
		m_AddressSize = sizeof(m_Address);
	}

	Client::~Client()
	{
	}

	bool Client::Init(string ip, int port)
	{
		WSADATA wsaData;
		WORD dllVersion = MAKEWORD(2, 2);

		if (WSAStartup(dllVersion, &wsaData) != 0)
		{
			MessageBox(NULL, "WinSock2 startup failed", "Network Error", MB_OK | MB_ICONERROR);
			return false;
		}

		m_Address.sin_addr.s_addr = inet_addr(ip.c_str());
		m_Address.sin_port = htons(port);
		m_Address.sin_family = AF_INET;

		if (!Connect())
		{
			MessageBox(NULL, "Failed to connect to server.", "Network Error", MB_OK | MB_ICONERROR);
			return false;
		}

		return true;
	}

	bool Client::Connect()
	{
		m_Connection = socket(AF_INET, SOCK_STREAM, NULL);
		if (connect(m_Connection, (SOCKADDR*)&m_Address, m_AddressSize) != 0)
		{
			return false;
		}

		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Thread, NULL, NULL, NULL);

		return true;
	}

	bool Client::CloseConnection()
	{
		if (closesocket(m_Connection) == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAENOTSOCK)
				return true;

			string errorMessage = "Failed to close the socket. Winsock Error: " + to_string(WSAGetLastError()) + ".";
			MessageBox(NULL, errorMessage.c_str(), "Network Error", MB_OK | MB_ICONERROR);
			return false;
		}

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

	void Client::Thread()
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
		if (g_pClient->CloseConnection())
		{
			OutputDebugString("Socket to the server was closed successfuly.\n");
		}
		else
		{
			OutputDebugString("Socket was not able to be closed.\n");
		}
	}
}