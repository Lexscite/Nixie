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
Time::Time()
    : seconds_per_count_(0),
      delta_time_(-1),
      base_time_(0),
      paused_time_(0),
      previous_time_(0),
      current_time_(0),
      is_stopped_(false) {
  __int64 counts_per_second;
  QueryPerformanceFrequency((LARGE_INTEGER*)&counts_per_second);
  seconds_per_count_ = 1 / (double)counts_per_second;
  Reset();
}

void Time::Start() {
  __int64 start_time;
  QueryPerformanceCounter((LARGE_INTEGER*)&start_time);

  if (is_stopped_) {
    paused_time_ += (start_time - stop_time_);
    previous_time_ = start_time;
    stop_time_ = 0;
    is_stopped_ = false;
  }
}

void Time::Stop() {
  if (!is_stopped_) {
    __int64 current_time;
    QueryPerformanceCounter((LARGE_INTEGER*)&current_time);

    stop_time_ = current_time;
    is_stopped_ = true;
  }
}

void Time::Reset() {
  __int64 current_time;
  QueryPerformanceCounter((LARGE_INTEGER*)&current_time);

  base_time_ = current_time;
  previous_time_ = current_time;
  stop_time_ = 0;
  is_stopped_ = false;
}

void Time::Tick() {
  if (is_stopped_) {
    delta_time_ = 0;
    return;
  }

  __int64 current_time;
  QueryPerformanceCounter((LARGE_INTEGER*)&current_time);
  current_time_ = current_time;
  delta_time_ = static_cast<float>((current_time_ - previous_time_) *
                                   seconds_per_count_);
  previous_time_ = current_time_;

  if (delta_time_ < 0) delta_time_ = 0;
}

float Time::GetDeltaTime() { return delta_time_; }

float Time::GetTime() const {
  if (is_stopped_)
    return static_cast<float>(((stop_time_ - paused_time_) - base_time_) *
                              seconds_per_count_);
  else
    return static_cast<float>(((current_time_ - paused_time_) - base_time_) *
                              seconds_per_count_);
}
}  // namespace voodoo