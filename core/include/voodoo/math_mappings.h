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

#ifndef VOODOO_MATH_MAPPINGS_H_
#define VOODOO_MATH_MAPPINGS_H_

#include "std_mappings.h"

#include <mathfu/quaternion.h>
#include <mathfu/rect.h>

namespace voodoo {
// Vector
template <class T, int d>
using Vector = mathfu::Vector<T, d>;
template <class T>
using vec2 = Vector<T, 2>;
template <class T>
using vec3 = Vector<T, 3>;
template <class T>
using vec4 = Vector<T, 4>;

typedef vec2<int> vec2i;
typedef vec2<uint> vec2ui;
typedef vec2<float> vec2f;
typedef vec2<double> vec2d;

typedef vec3<int> vec3i;
typedef vec3<uint> vec3ui;
typedef vec3<float> vec3f;
typedef vec3<double> vec3d;

typedef vec4<int> vec4i;
typedef vec4<uint> vec4ui;
typedef vec4<float> vec4f;
typedef vec4<double> vec4d;

typedef vec2i int2;
typedef vec3i int3;
typedef vec4i int4;

typedef vec2ui uint2;
typedef vec3ui uint3;
typedef vec4ui uint4;

typedef vec2f float2;
typedef vec3f float3;
typedef vec4f float4;

typedef vec2d double2;
typedef vec3d double3;
typedef vec4d double4;

// Matrix
template <class T, int rows, int columns>
using Matrix = mathfu::Matrix<T, rows, columns>;
template <class T>
using matrix1x1 = Matrix<T, 2, 2>;
template <class T>
using matrix2x2 = Matrix<T, 2, 2>;
template <class T>
using matrix3x3 = Matrix<T, 3, 3>;
template <class T>
using matrix4x3 = Matrix<T, 4, 3>;
template <class T>
using matrix4x4 = Matrix<T, 4, 4>;

typedef matrix1x1<int> int1x1;
typedef matrix2x2<int> int2x2;
typedef matrix3x3<int> int3x3;
typedef matrix4x3<int> int4x3;
typedef matrix4x4<int> int4x4;

typedef matrix1x1<uint> uint1x1;
typedef matrix2x2<uint> uint2x2;
typedef matrix3x3<uint> uint3x3;
typedef matrix4x3<uint> uint4x3;
typedef matrix4x4<uint> uint4x4;

typedef matrix1x1<float> float1x1;
typedef matrix2x2<float> float2x2;
typedef matrix3x3<float> float3x3;
typedef matrix4x3<float> float4x3;
typedef matrix4x4<float> float4x4;

typedef matrix1x1<double> double1x1;
typedef matrix2x2<double> double2x2;
typedef matrix3x3<double> double3x3;
typedef matrix4x3<double> double4x3;
typedef matrix4x4<double> double4x4;

// Quaternion
template <class T>
using Quaternion = mathfu::Quaternion<T>;

typedef Quaternion<float> quatf;
typedef Quaternion<double> quatd;

// Rectangle
template <class T>
using Rect = mathfu::Rect<T>;

typedef Rect<int> recti;
typedef Rect<uint> rectui;
typedef Rect<float> rectf;
typedef Rect<double> rectd;
}  // namespace voodoo

#endif