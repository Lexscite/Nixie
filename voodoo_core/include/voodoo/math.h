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

#include <mathfu/quaternion.h>
#include <mathfu/rect.h>
#include <mathfu/constants.h>

namespace voodoo {
template <class T>
// Vector
using Vector2 = mathfu::Vector<T, 2>;

template <class T>
using Vector3 = mathfu::Vector<T, 3>;

template <class T>
using Vector4 = mathfu::Vector<T, 4>;

using Vector2f = Vector2<float>;
using Vector3f = Vector3<float>;
using Vector4f = Vector4<float>;

// Quaternion
using Quaternion = mathfu::Quaternion<float>;

// Matrix
template <class T>
using Matrix3x3 = mathfu::Matrix<T, 3>;

template <class T>
using Matrix4x3 = mathfu::Matrix<T, 4, 3>;

template <class T>
using Matrix4x4 = mathfu::Matrix<T, 4>;

using Matrix3x3f = Matrix3x3<float>;
using Matrix4x3f = Matrix4x3<float>;
using Matrix4x4f = Matrix4x4<float>;

// Rectangle
template <class T>
using Rect = mathfu::Rect<T>;

using Rectf = Rect<float>;

// Constants
static constexpr float kPi = mathfu::kPi;

// Functions
template <class T>
const auto clamp = mathfu::Clamp<T>;

inline float clamp_color(float v) {
  return clamp<float>(v, 0.0f, 255.0f) / 255.0f;
}

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