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

#include "../include/voodoo/camera.h"

// Components
#include "../include/voodoo/transform.h"

namespace voodoo {
Camera::Camera() : fov_(kPiDiv4),
                   aspect_ratio_(8.0f / 6.0f),
                   z_near_(0.1f),
                   z_far_(1000.0f) {}

float4x4 Camera::GetViewMatrix() {
  vec3f pos = GetTransform()->GetPosition();
  vec3f at = pos + GetTransform()->GetForward();
  vec3f up = GetTransform()->GetUp();

  return float4x4::LookAt(at, pos, up, -1.0f);
}

float4x4 Camera::GetProjectionMatrix() {
  return float4x4::Perspective(fov_, aspect_ratio_, z_near_, z_far_, -1.0f);
}
}  // namespace voodoo