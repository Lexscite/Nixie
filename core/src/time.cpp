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

#include "../include/voodoo/time.h"

// Retrieving QueryPerformanceFrequency and QueryPerformanceCounter functions.
// TODO: Find out cross-platform solution
#ifdef _WIN32
#include <windows.h>
#endif  // _WIN32

namespace voodoo {
double Time::per_tick_ = GetPerTickTime();
float Time::delta_ = -1;
int64 Time::current_ = GetCurrentTimestamp();
int64 Time::previous_ = Time::current_;
int64 Time::base_ = Time::current_;
int64 Time::pause_ = 0;
int64 Time::stop_ = 0;
bool Time::stopped_ = false;

int64 Time::GetCurrentTimestamp() {
  int64 timestamp;
  QueryPerformanceCounter((LARGE_INTEGER*)&timestamp);
  return timestamp;
}

double Time::GetPerTickTime() {
  int64 frequency;
  QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
  return 1 / static_cast<double>(frequency);
}

void Time::Start() {
  if (stopped_) {
    auto start_time = GetCurrentTimestamp();
    pause_ += (start_time - stop_);
    previous_ = start_time;
    stop_ = 0;
    stopped_ = false;
  }
}

void Time::Stop() {
  if (!stopped_) {
    stop_ = GetCurrentTimestamp();
    stopped_ = true;
  }
}

void Time::Reset() {
  auto current_time = GetCurrentTimestamp();
  base_ = current_time;
  previous_ = current_time;
  stop_ = 0;
  stopped_ = false;
}

void Time::Tick() {
  if (stopped_) {
    delta_ = 0;
  } else {
    current_ = GetCurrentTimestamp();
    delta_ = static_cast<float>((current_ - previous_) * per_tick_);
    previous_ = current_;
    if (delta_ < 0) delta_ = 0;
  }
}

float Time::GetDeltaTime() {
  return delta_;
}

float Time::GetTime() {
  auto from = stopped_ ? stop_ : current_;
  return static_cast<float>(((from - pause_) - base_) * per_tick_);
}
}  // namespace voodoo