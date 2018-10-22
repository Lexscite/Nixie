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

#ifndef VOODOO_COLOR_H_
#define VOODOO_COLOR_H_

#include "math.h"

namespace voodoo {
struct color {
 public:
  color() {}

  color(const float& s)
      : r(clamp_color(s)),
        g(r),
        b(r),
        a(1) {}

  color(const float& r, const float& g, const float& b)
      : r(clamp_color(r)),
        g(clamp_color(g)),
        b(clamp_color(b)),
        a(1) {}

  color(const float& r, const float& g, const float& b, const float& a)
      : r(clamp_color(r)),
        g(clamp_color(g)),
        b(clamp_color(b)),
        a(clamp_color(a)) {}

  color(const vec3f& v)
      : r(clamp_color(v.x)),
        g(clamp_color(v.y)),
        b(clamp_color(v.z)),
        a(1) {}

  color(const vec3f& v, float a)
      : r(clamp_color(v.x)),
        g(clamp_color(v.y)),
        b(clamp_color(v.z)),
        a(clamp_color(a)) {}

  color(const vec4f& v)
      : r(clamp_color(v.x)),
        g(clamp_color(v.y)),
        b(clamp_color(v.z)),
        a(clamp_color(v.w)) {}

  inline operator float*() const { return new float[4]{r, g, b, a}; };

 public:
  float r, g, b, a;
};
}  // namespace voodoo

#endif