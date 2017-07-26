#include "Server.h"

using namespace NixieServer;

int main()
{
	Server* pServer = new Server;

	if (!pServer->Start())
	{
		return 0;
	}

	return 0;
}