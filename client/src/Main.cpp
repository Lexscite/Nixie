#include "core/Game.h"

using NixieClient::Game;

#ifdef DEBUG
class ConsoleBuffer : public std::streambuf {
public:
	ConsoleBuffer() {
		setp(0, 0);
	}

	virtual int_type overflow(int_type c = traits_type::eof()) {
		return fputc(c, stdout) == EOF ? traits_type::eof() : c;
	}
};
#endif // DEBUG

int WINAPI WinMain(__in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd)
{
	if (AllocConsole())
	{
		freopen("CONOUT$", "w", stdout);
		SetConsoleTitle("Debug Console");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
	}

#ifdef DEBUG
	ConsoleBuffer consoleBuffer;
	std::streambuf *streambuffer = std::cout.rdbuf(&consoleBuffer);
#endif // DEBUG

	Game* pGame = new Game(hInstance);
	if (pGame->Init())
	{
		pGame->Run();
	}
	else
		return 1;

	delete pGame;
	pGame = nullptr;

#ifdef DEBUG
	std::cout.rdbuf(sb);
#endif // DEBUG

	return 0;
}