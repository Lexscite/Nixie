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

#include "../include/voodoo/logger.h"

namespace voodoo {
Log::Log() {
  log_file_.open("log.txt");

#ifdef VOODOO_LOG_CONSOLE_ENABLED
  using namespace std;
  if (AllocConsole()) {
    freopen("CONOUT$", "w", stdout);
    SetConsoleTitle(L"voodoo | Debug Console");
    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE),
        FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
  }

  cout_buffer_ = cout.rdbuf(&console_buffer_);
  cerr_buffer_ = cerr.rdbuf(&console_buffer_);
#endif  // VOODOO_LOG_CONSOLE_ENABLED
}

Log::~Log() {
  log_file_.close();

#ifdef VOODOO_LOG_CONSOLE_ENABLED
  using namespace std;
  cout.rdbuf(cout_buffer_);
  cout.rdbuf(cerr_buffer_);
#endif  // VOODOO_LOG_CONSOLE_ENABLED
}

Log& Log::Get() {
  static Log instance;
  return instance;
}

void Log::Info(std::string message) {
  Write(message, kLogEntryLevelInfo);
}

void Log::Warning(std::string message) {
  Write(message, kLogEntryLevelWarning);
}

void Log::Error(std::string message) {
  Write(message, kLogEntryLevelError);
}

void Log::Write(std::string message) {
  Info(message);
}

void Log::Write(std::string message, LogEntryLevel level) {
  using namespace std;
  string prefix;
  switch (level) {
    case kLogEntryLevelWarning:
      prefix = "Warning: ";
      break;
    case kLogEntryLevelError:
      prefix = "Error: ";
      break;
    default:
      prefix = "";
      break;
  }

  Get().log_file_ << prefix << message << endl;

#ifdef VOODOO_LOG_CONSOLE_ENABLED
  cout << prefix << message << endl;
#endif  // VOODOO_LOG_CONSOLE_ENABLED
}

void Log::Throw(std::string message) {
  using namespace std;
  Error(message);
  throw runtime_error(message);
}
}  // namespace voodoo