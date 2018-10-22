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

#include "math_mappings.h"

#include <mathfu/constants.h>

namespace voodoo {
// Constants
static constexpr float kPi = mathfu::kPi;
static constexpr float kPiDiv2 = kPi / 2;
static constexpr float kPiDiv4 = kPi / 4;

static const vec2i kVec2iZeros(0, 0);
static const vec2i kVec2iOnes(1, 1);
static const vec2i kVec2iX(1, 0);
static const vec2i kVec2iY(0, 1);

static const vec3i kVec3iZeros(0, 0, 0);
static const vec3i kVec3iOnes(1, 1, 1);
static const vec3i kVec3iX(1, 0, 0);
static const vec3i kVec3iY(0, 1, 0);
static const vec3i kVec3iZ(0, 0, 1);

static const vec4i kVec4iZeros(0, 0, 0, 0);
static const vec4i kVec4iOnes(1, 1, 1, 1);
static const vec4i kVec4iX(1, 0, 0, 0);
static const vec4i kVec4iY(0, 1, 0, 0);
static const vec4i kVec4iZ(0, 0, 1, 0);
static const vec4i kVec4iW(0, 0, 0, 1);

static const vec2ui kVec2uiZeros(0, 0);
static const vec2ui kVec2uiOnes(1, 1);
static const vec2ui kVec2uiX(1, 0);
static const vec2ui kVec2uiY(0, 1);

static const vec3ui kVec3uiZeros(0, 0, 0);
static const vec3ui kVec3uiOnes(1, 1, 1);
static const vec3ui kVec3uiX(1, 0, 0);
static const vec3ui kVec3uiY(0, 1, 0);
static const vec3ui kVec3uiZ(0, 0, 1);

static const vec4ui kVec4uiZeros(0, 0, 0, 0);
static const vec4ui kVec4uiOnes(1, 1, 1, 1);
static const vec4ui kVec4uiX(1, 0, 0, 0);
static const vec4ui kVec4uiY(0, 1, 0, 0);
static const vec4ui kVec4uiZ(0, 0, 1, 0);
static const vec4ui kVec4uiW(0, 0, 0, 1);

static const vec2f kVec2fZeros(0.0f, 0.0f);
static const vec2f kVec2fOnes(1.0f, 1.0f);
static const vec2f kVec2fX(1.0f, 0.0f);
static const vec2f kVec2fY(0.0f, 1.0f);

static const vec3f kVec3fZeros(0.0f, 0.0f, 0.0f);
static const vec3f kVec3fOnes(1.0f, 1.0f, 1.0f);
static const vec3f kVec3fX(1.0f, 0.0f, 0.0f);
static const vec3f kVec3fY(0.0f, 1.0f, 0.0f);
static const vec3f kVec3fZ(0.0f, 0.0f, 1.0f);

static const vec4f kVec4fZeros(0.0f, 0.0f, 0.0f, 0.0f);
static const vec4f kVec4fOnes(1.0f, 1.0f, 1.0f, 1.0f);
static const vec4f kVec4fX(1.0f, 0.0f, 0.0f, 0.0f);
static const vec4f kVec4fY(0.0f, 1.0f, 0.0f, 0.0f);
static const vec4f kVec4fZ(0.0f, 0.0f, 1.0f, 0.0f);
static const vec4f kVec4fW(0.0f, 0.0f, 0.0f, 1.0f);

static const vec2d kVec2dZeros(0.0, 0.0);
static const vec2d kVec2dOnes(1.0, 1.0);
static const vec2d kVec2dX(1.0, 0.0);
static const vec2d kVec2dY(0.0, 1.0);

static const vec3d kVec3dZeros(0.0, 0.0, 0.0);
static const vec3d kVec3dOnes(1.0, 1.0, 1.0);
static const vec3d kVec3dX(1.0, 0.0, 0.0);
static const vec3d kVec3dY(0.0, 1.0, 0.0);
static const vec3d kVec3dZ(0.0, 0.0, 1.0);

static const vec4d kVec4dZeros(0.0, 0.0, 0.0, 0.0);
static const vec4d kVec4dOnes(1.0, 1.0, 1.0, 1.0);
static const vec4d kVec4dX(1.0, 0.0, 0.0, 0.0);
static const vec4d kVec4dY(0.0, 1.0, 0.0, 0.0);
static const vec4d kVec4dZ(0.0, 0.0, 1.0, 0.0);
static const vec4d kVec4dW(0.0, 0.0, 0.0, 1.0);

static const quatf kQuatfIdentity(1.0f, 0.0f, 0.0f, 0.0f);
static const quatd kQuatIddentity(1.0, 0.0, 0.0, 0.0);

static const float4x3 kAffineIdentity(1.0f, 0.0f, 0.0f, 0.0f,
                                      0.0f, 1.0f, 0.0f, 0.0f,
                                      0.0f, 0.0f, 1.0f, 0.0f);

// Functions
template <class T>
const auto clamp = mathfu::Clamp<T>;

const auto clampf = clamp<float>;

inline float clamp_color(float v) {
  return clampf(v, 0.0f, 255.0f) / 255.0f;
}

template <class T>
inline Vector<T, 3> cross(const Vector<T, 3>& v1, const Vector<T, 3>& v2) {
  return Vector<T, 3>::CrossProduct(v1, v2);
}

template <class T>
inline T rtod(const T& r) {  // radians to degrees
  return (r * T(180)) / mathfu::kPi;
}

template <class T>
inline T dtor(const T& d) {  // degrees to radians
  return (d * mathfu::kPi) / 180;
}

const auto dtorf = dtor<float>;

inline float3 dtorv(const float3& v) {
  return float3(dtorf(v.x), dtorf(v.y), dtorf(v.z));
}
}  // namespace voodoo

#endif