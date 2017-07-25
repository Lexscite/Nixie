#include "Client.h"
#include <tchar.h>
namespace NixieClient
{
	Client::Client()
	{
	}

	Client::~Client()
	{
	}

	bool Client::Connect(char* ip, int port)
	{
		WSAStartup(MAKEWORD(2, 2), &m_SocketVersion);

		m_Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (m_Socket == INVALID_SOCKET)
		{
			MessageBox(NULL, "Invalid socket", "Connection Error", MB_OK);
			return false;
		}

		m_SocketAddress.sin_family = AF_INET;
		m_SocketAddress.sin_addr.s_addr = inet_addr(ip);
		m_SocketAddress.sin_port = htons(port);

		if (connect(m_Socket, (struct sockaddr*)&m_SocketAddress, sizeof(m_SocketAddress)) == SOCKET_ERROR)
		{
			OutputDebugString("\nERROR CONNECTING TO SERVER\n\n");
			return 0;
		}

		return true;
	}

	int Client::Send(char * data, int length, int clientId)
	{
		int messageLength = send(m_Socket, data, length, NULL);
		if (messageLength < 0)
		{
			return 0;
		}

		return messageLength;
	}

	int Client::Recieve(char* data, int length, int clientId)
	{
		int messageLength;
		messageLength = recv(m_Socket, data, length, NULL);
		if (messageLength < 0)
		{
			return 0;
		}

		return messageLength;
	}

	bool Client::CloseSocket()
	{
		closesocket(m_Socket);
		WSACleanup();

		return true;
	}
}
