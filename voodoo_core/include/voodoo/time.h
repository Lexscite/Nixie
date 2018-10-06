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

#ifndef VOODOO_TIME_H_
#define VOODOO_TIME_H_

namespace voodoo {
class Time {
 public:
  static Time* Get();

  void Start();
  void Stop();
  void Reset();
  void Tick();

  float GetTime() const;
  static float GetDeltaTime();

 private:
  Time();

 private:
  static Time* singleton_;

  double seconds_per_count_;
  double delta_time_;

  __int64 base_time_;
  __int64 paused_time_;
  __int64 stop_time_;
  __int64 previous_time_;
  __int64 current_time_;

  bool is_stopped_;
};
}  // namespace voodoo

#endif