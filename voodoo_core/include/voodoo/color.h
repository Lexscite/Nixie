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

#ifndef VOODOO_COLOR_H_
#define VOODOO_COLOR_H_

#include "math.h"
#include "vector.h"

namespace voodoo {
class Color {
 public:
  Color(){};
  Color(const float& s) {
    float cs = ClampChannel(s);
    r = g = b = cs;
  }
  Color(const float& r, const float& g, const float& b)
      : r(ClampChannel(r)), g(ClampChannel(g)), b(ClampChannel(b)), a(1) {}
  Color(const float& r, const float& g, const float& b, const float& a)
      : r(ClampChannel(r)),
        g(ClampChannel(g)),
        b(ClampChannel(b)),
        a(ClampChannel(a)) {}
  Color(const Vector3<float>& v)
      : r(ClampChannel(v.x)),
        g(ClampChannel(v.y)),
        b(ClampChannel(v.z)),
        a(1) {}
  Color(const Vector3<float>& v, float a)
      : r(ClampChannel(v.x)),
        g(ClampChannel(v.y)),
        b(ClampChannel(v.z)),
        a(ClampChannel(a)) {}

  inline operator float*() const { return new float[4]{r, g, b, a}; };

 private:
  float ClampChannel(float value) {
    return Clamp<float>(value, 0.0f, 255.0f) / 255.0f;
  }

 public:
  float r, g, b, a;
};
}  // namespace voodoo

#endif