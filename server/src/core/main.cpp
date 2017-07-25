#include "Server.h"

using namespace NixieServer;
using namespace std;

int main()
{
	cout << "Welcome to Nixie server! Author Vyacheslav (Lexscite) Elchin <lexscite@gmail.com>" << endl << endl;

	Server* pServer = new Server;
	if (!pServer)
	{
		cout << "(E) Failed to create server." << endl;
		Sleep(4000);
		return 1;
	}
	cout << "(OK) Server created." << endl;

	if (!pServer->Start(1234))
	{
		cout << "(E) Failed to start server." << endl;
		Sleep(4000);
		return 1;
	}
	cout << "(OK) Server started" << endl;

	Sleep(4000);
	pServer->CloseSocket();
	delete pServer;
	pServer = nullptr;

	return 0;
}