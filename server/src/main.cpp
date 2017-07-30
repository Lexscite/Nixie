#include "core/Server.h"

using namespace NixieServer;

int main()
{
	Server* pServer = new Server;

	if (pServer->Start(1111))
		pServer->Run();
	else
	{
		cout << "Cannot start the server." << endl;
		Sleep(4000);
		return 1;
	}

	return 0;
}