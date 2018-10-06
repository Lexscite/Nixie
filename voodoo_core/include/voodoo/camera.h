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

#ifndef VOODOO_CAMERA_H_
#define VOODOO_CAMERA_H_

#include "component.h"

namespace voodoo {
class Camera : public Component {
 public:
  Camera();

  Matrix4x4f GetViewMatrix();
  Matrix4x4f GetProjectionMatrix();

 private:
  virtual bool OnInit() override;
  virtual bool OnUpdate() override;

  void CalculateViewMatrix();
  void CalculateProjectionMatrix();

 private:
  float fov_, aspect_ratio_, z_near_, z_far_;

  Matrix4x4f view_matrix_;
  Matrix4x4f projection_matrix_;
};
}  // namespace voodoo

#endif