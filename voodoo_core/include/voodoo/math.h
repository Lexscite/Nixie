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

#ifndef VOODOO_MATH_H_
#define VOODOO_MATH_H_

#include <mathfu/constants.h>
#include <mathfu/utilities.h>

#include "vector.h"

namespace voodoo {
namespace math {
static constexpr float kPi = mathfu::kPi;
}  // namespace math

template <class T>
const auto clamp = mathfu::Clamp<T>;

// Radians to degrees
template <class T>
inline T rtod(const T& r) {
  return (r * T(180)) / mathfu::kPi;
}

// Degrees to radians
template <class T>
inline T dtor(const T& d) {
  return (d * mathfu::kPi) / 180;
}

const auto dtorf = dtor<float>;

inline Vector3f dtorv(const Vector3f& v) {
  return Vector3f(dtorf(v.x),
                  dtorf(v.y),
                  dtorf(v.z));
}
}  // namespace voodoo

#endif