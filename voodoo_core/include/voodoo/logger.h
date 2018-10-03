#ifndef VOODOO_LOG_H_
#define VOODOO_LOG_H_

#if defined _WIN32 && _DEBUG
// Suppress warnings for freopen()
#define _CRT_SECURE_NO_WARNINGS
// Windows console allocation enabled
#define VOODOO_LOG_CONSOLE_ENABLED
// AllocConsole()
#include <windows.h>
#endif  // _WIN32 &&_DEBUG

#include <iostream>
#include <string>
#include <fstream>

namespace voodoo
{
#ifdef VOODOO_LOG_CONSOLE_ENABLED
	class ConsoleBuffer : public std::streambuf {
	public:
		ConsoleBuffer()
		{
			setp(0, 0);
		}

		virtual int_type overflow(int_type c = traits_type::eof())
		{
			return fputc(c, stdout) == EOF ? traits_type::eof() : c;
		}
	};
#endif

	class Logger final
	{
	public:
		~Logger();

		static void Write(std::string s);

	private:
		Logger();

		static Logger& Get();

	private:
		std::ofstream fs_;

#ifdef VOODOO_LOG_CONSOLE_ENABLED
	private:
		static void WriteToConsole(std::string s);

	private:
		ConsoleBuffer console_buffer_;
		std::streambuf* cout_buffer_;
		std::streambuf* cerr_buffer_;
#endif
	};
}

#endif