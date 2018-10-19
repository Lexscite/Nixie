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

namespace voodoo {
namespace math {
static constexpr float pi = mathfu::kPi;
}

template <class T>
const auto Clamp = mathfu::Clamp<T>;

template <class T>
inline T RadianToDegree(const T& r) {
  return (r * T(180)) / mathfu::kPi;
}

template <class T>
inline T DegreeToRadian(const T& d) {
  return (d * mathfu::kPi) / 180;
}
}  // namespace voodoo

#endif