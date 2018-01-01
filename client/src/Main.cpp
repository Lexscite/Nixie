#include "base/app.h"

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
#endif _DEBUG

int WINAPI WinMain(__in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd)
{
#ifdef _DEBUG
	if (AllocConsole())
	{
		freopen("CONOUT$", "w", stdout);
		SetConsoleTitle("Nixie | Debug Console");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
	}

	ConsoleBuffer console_buffer;
	std::streambuf *cout_buffer = std::cout.rdbuf(&console_buffer);
	std::streambuf *cerr_buffer = std::cerr.rdbuf(&console_buffer);
#endif

	int exit_code = 0;

	App* app = App::GetSingleton();
	if (app->Init(hInstance))
		exit_code = app->Run();

	safe_release(app);

#ifdef _DEBUG
	std::cout.rdbuf(cout_buffer);
	std::cout.rdbuf(cerr_buffer);
#endif

	return exit_code;
}