#include "server.h"

int main()
{
	CServer* pServer = CServer::Get();

	if (pServer->Start(1111))
		pServer->Run();
	else
	{
		std::cout << "Cannot start the server." << std::endl;
		Sleep(4000);
		return 1;
	}

	return 0;
}