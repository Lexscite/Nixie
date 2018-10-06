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
// along with Foobar.  If not, see <https://www.gnu.org/licenses/>.

#include "../include/voodoo/logger.h"

namespace voodoo {
Logger::Logger() {
  fs_.open("log.txt");

#ifdef VOODOO_LOG_CONSOLE_ENABLED
  if (AllocConsole()) {
    freopen("CONOUT$", "w", stdout);
    SetConsoleTitle(L"voodoo | Debug Console");
    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE),
        FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
  }

  cout_buffer_ = std::cout.rdbuf(&console_buffer_);
  cerr_buffer_ = std::cerr.rdbuf(&console_buffer_);
#endif
}

Logger::~Logger() {
  fs_.close();

#ifdef VOODOO_LOG_CONSOLE_ENABLED
  std::cout.rdbuf(cout_buffer_);
  std::cout.rdbuf(cerr_buffer_);
#endif
}

Logger& Logger::Get() {
  static Logger instance;
  return instance;
}

void Logger::Write(std::string s) {
  Get().fs_ << s << std::endl;

#ifdef VOODOO_LOG_CONSOLE_ENABLED
  WriteToConsole(s);
#endif
}

#ifdef VOODOO_LOG_CONSOLE_ENABLED
void Logger::WriteToConsole(std::string s) { std::cout << s << std::endl; }
#endif
}  // namespace voodoo