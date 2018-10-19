// This file is part of Voodoo Engine.
//
// Voodoo Engine is free software : you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Voodoo Engine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Voodoo Engine.  If not, see <https://www.gnu.org/licenses/>.

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

#include <fstream>
#include <iostream>
#include <string>

namespace voodoo {
#ifdef VOODOO_LOG_CONSOLE_ENABLED
class ConsoleBuffer : public std::streambuf {
 public:
  ConsoleBuffer() { setp(0, 0); }

  virtual int_type overflow(int_type c = traits_type::eof()) {
    return fputc(c, stdout) == EOF ? traits_type::eof() : c;
  }
};
#endif

enum LogEntryLevel {
  kLogEntryLevelInfo = 0,
  kLogEntryLevelWarning = 1,
  kLogEntryLevelError = 2,
};

struct LogEntry {
public:
  std::string body;
  LogEntryLevel level;
};

class Log final {
 public:
  ~Log();

  static void Info(std::string message);
  static void Warning(std::string message);
  static void Error(std::string message);

  static void Write(std::string message);
  static void Write(std::string message, LogEntryLevel level);

  static void Throw(std::string message);

 private:
  Log();

  static Log& Get();

 private:
  std::ofstream log_file_;

#ifdef VOODOO_LOG_CONSOLE_ENABLED
 private:
  static void WriteToConsole(std::string s);

 private:
  ConsoleBuffer console_buffer_;
  std::streambuf* cout_buffer_;
  std::streambuf* cerr_buffer_;
#endif
};
}  // namespace voodoo

#endif