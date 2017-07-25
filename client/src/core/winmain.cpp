#include "Game.h"

using NixieClient::Game;
using namespace std;

int WINAPI WinMain(__in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd)
{
	Game* game = new Game(hInstance);

	if (game->Init())
	{
		game->Run();
	}
	else
	{
		return 1;
	}

	SafeDelete(game);

	return 0;
}