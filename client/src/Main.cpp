#include "core/Game.h"

using std::cout;
using std::cerr;
using std::streambuf;

#ifdef _DEBUG
class ConsoleBuffer : public streambuf {
public:
	ConsoleBuffer() {
		setp(0, 0);
	}

	virtual int_type overflow(int_type c = traits_type::eof()) {
		return fputc(c, stdout) == EOF ? traits_type::eof() : c;
	}
};
#endif // _DEBUG

int WINAPI WinMain(__in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd)
{
	if (AllocConsole())
	{
		freopen("CONOUT$", "w", stdout);
		SetConsoleTitle("Debug Console");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
	}

#ifdef _DEBUG
	ConsoleBuffer consoleBuffer;
	streambuf *coutBuffer = cout.rdbuf(&consoleBuffer);
	streambuf *cerrBuffer = cerr.rdbuf(&consoleBuffer);
#endif // _DEBUG

	Game* pGame = new Game(hInstance);
	if (pGame->Init())
	{
		pGame->Run();
	}
	else
		return 1;

	delete pGame;
	pGame = nullptr;

#ifdef _DEBUG
	cout.rdbuf(coutBuffer);
	cout.rdbuf(cerrBuffer);
#endif // _DEBUG

	return 0;
}