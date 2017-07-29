#include "Client.h"

static NXNetwork::Client* g_pClient;

namespace NXNetwork
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
			cerr << "WSAStartup failed. Error code: " << WSAGetLastError() << endl;
			return false;
		}

		m_Address.sin_addr.s_addr = inet_addr(ip.c_str());
		m_Address.sin_port = htons(port);
		m_Address.sin_family = AF_INET;

		return true;
	}

	bool Client::Connect()
	{
		m_Connection = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (connect(m_Connection, (SOCKADDR*)&m_Address, m_AddressSize) != 0)
		{
			cerr << "Unable to connect. Error code: " << WSAGetLastError() << endl;
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

			cerr << "Failed to close the connection. Error code: " << WSAGetLastError() << endl;
			return false;
		}

		return true;
	}

	bool Client::Send(char* data, int totalBytes)
	{
		int sentBytes = 0;
		while (sentBytes < totalBytes)
		{
			int result = send(m_Connection, data + sentBytes, totalBytes - sentBytes, NULL);
			if (result == SOCKET_ERROR)
			{
				cerr << "Failed to send data. Error code: " << WSAGetLastError() << endl;
				return false;
			}
			else if (result == 0)
			{
				int iError = WSAGetLastError();
				if (iError == WSAEWOULDBLOCK)
					cerr << "Failed to send data. Error: WSAEWOULDBLOCK" << endl;
				else
					cerr << "Failed to send data. Error code: " << iError << endl;

				return false;
			}

			sentBytes += result;
		}

		return true;
	}

	bool Client::Recieve(char* data, int totalBytes)
	{
		int recievedBytes = 0;
		while (recievedBytes < totalBytes)
		{
			int result = recv(m_Connection, data + recievedBytes, totalBytes - recievedBytes, NULL);
			if (result == SOCKET_ERROR)
			{
				cerr << "Failed to send data. Error code: " << WSAGetLastError() << endl;
				return false;
			}
			else if (result == 0)
			{
				int iError = WSAGetLastError();
				if (iError == WSAEWOULDBLOCK)
					cerr << "Failed to send data. Error: WSAEWOULDBLOCK" << endl;
				else
					cerr << "Failed to send data. Error code: " << iError << endl;

				return false;
			}

			recievedBytes += result;
		}

		return true;
	}

	bool Client::SendInt32(int32_t data)
	{
		data = htonl(data);
		if (!Send((char*)&data, sizeof(int32_t)))
			return false;
		
		return true;
	}

	bool Client::GetInt32(int32_t &data)
	{
		if (!Recieve((char*)&data, sizeof(int32_t)))
			return false;
		data = ntohl(data);
		
		return true;
	}

	bool Client::SendPacketType(PacketType data)
	{
		if (!SendInt32((int32_t)data))
			return false;
		
		return true;
	}

	bool Client::GetPacketType(PacketType &data)
	{
		int32_t dataInt;
		if (!GetInt32(dataInt))
			return false;
		data = (PacketType)dataInt;
		
		return true;
	}

	bool Client::SendString(string &data)
	{
		int32_t bufferLength = (int32_t)data.size();

		if (!SendInt32(bufferLength))
			return false;

		if (!Send((char*)data.c_str(), bufferLength))
			return false;

		return true;
	}

	bool Client::GetString(string &data)
	{
		int32_t bufferLength;

		if (!GetInt32(bufferLength))
			return false;

		char* buffer = new char[bufferLength + 1];
		buffer[bufferLength] = '\0';

		if (!Recieve(buffer, bufferLength))
		{
			delete[] buffer;
			return false;
		}

		data = buffer;
		delete[] buffer;

		return true;
	}

	bool Client::ProcessPacket(PacketType packetType)
	{
		switch (packetType)
		{
			case PacketType::LoginData:
			{
				break;
			}
			case PacketType::ChatMessage:
			{
				string message;
				if (!GetString(message))
					return false;

				cout << "Message recieved: " << message << endl;
				break;
			}
			default:
				cerr << "Unrecognized packet type" << endl;
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
			cout << "Socket to the server was closed successfuly" << endl;
		else
			cerr << "Socket is't able to be closed" << endl;
	}
}