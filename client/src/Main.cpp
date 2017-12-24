#include "engine/Engine.h"

#ifdef _DEBUG
class ConsoleBuffer : public std::streambuf {
public:
	ConsoleBuffer() {
		setp(0, 0);
	}

	virtual int_type overflow(int_type c = traits_type::eof()) {
		return fputc(c, stdout) == EOF ? traits_type::eof() : c;
	}
};
#endif

int WINAPI WinMain(__in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd)
{
	if (AllocConsole())
	{
		freopen("CONOUT$", "w", stdout);
		SetConsoleTitle("Nixie | Debug Console");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
	}

#ifdef _DEBUG
	ConsoleBuffer consoleBuffer;
	std::streambuf *coutBuffer = std::cout.rdbuf(&consoleBuffer);
	std::streambuf *cerrBuffer = std::cerr.rdbuf(&consoleBuffer);
#endif

	Engine* engine = Engine::GetSingleton();
	if (engine->Init(hInstance))
	{
		engine->Run();
	}
	else
		return 1;

	safe_release(engine);

#ifdef _DEBUG
	std::cout.rdbuf(coutBuffer);
	std::cout.rdbuf(cerrBuffer);
#endif

	return 0;
}