#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <windows.h>

#pragma comment(lib,"ws2_32.lib")

namespace NixieClient
{
	class Client
	{
	public:
		Client();
		~Client();

		bool Connect();

	public:
		WSAData m_WSAData;
		WORD m_DllVersion;
		SOCKADDR_IN m_Address;
	};
}

#endif // !CLIENT_H