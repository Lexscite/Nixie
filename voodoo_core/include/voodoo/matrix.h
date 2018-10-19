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

#ifndef VOODOO_MATRIX_H_
#define VOODOO_MATRIX_H_

#include <mathfu/matrix.h>

namespace voodoo {
template <class T>
using Matrix3x3 = mathfu::Matrix<T, 3>;

template <class T>
using Matrix4x3 = mathfu::Matrix<T, 4, 3>;

template <class T>
using Matrix4x4 = mathfu::Matrix<T, 4>;

using Matrix3x3f = Matrix3x3<float>;
using Matrix4x3f = Matrix4x3<float>;
using Matrix4x4f = Matrix4x4<float>;
}  // namespace voodoo

#endif