#include "core/Server.h"

using namespace NixieServer;

int main()
{
	Server* pServer = new Server;

	if (!pServer->Start(1111))
	{
		cout << "Cannot start the server." << endl;
		Sleep(4000);
		return 0;
	}

	pServer->Run();

	return 0;
}