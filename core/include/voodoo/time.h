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

#ifndef VOODOO_TIME_H_
#define VOODOO_TIME_H_

#include "std_mappings.h"

namespace voodoo {
class Engine;

class Time {
 private:
  friend Engine;

 public:
  static float GetTime();
  static float GetDeltaTime();

 private:
  static void Start();
  static void Stop();
  static void Reset();
  static void Tick();

  static int64 GetCurrentTimestamp();
  static double GetPerTickTime();

 private:
  static double per_tick_;
  static float delta_;

  static int64 base_;
  static int64 pause_;
  static int64 stop_;
  static int64 previous_;
  static int64 current_;

  static bool stopped_;
};
}  // namespace voodoo

#endif  // VOODOO_TIME_H_