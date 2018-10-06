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

#ifndef VOODOO_VECTOR_H_
#define VOODOO_VECTOR_H_

#include <mathfu/vector.h>

namespace voodoo {
template <class T>
using Vector2 = mathfu::Vector<T, 2>;

template <class T>
using Vector3 = mathfu::Vector<T, 3>;

template <class T>
using Vector4 = mathfu::Vector<T, 4>;

using Vector2f = Vector2<float>;
using Vector3f = Vector3<float>;
using Vector4f = Vector4<float>;
}  // namespace voodoo

#endif