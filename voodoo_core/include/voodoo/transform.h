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

#ifndef VOODOO_TRANSFORM_H_
#define VOODOO_TRANSFORM_H_

#include "component.h"

#include "math.h"

namespace voodoo {
class Transform : public Component {
 public:
  Transform();

  Matrix4x4f GetWorldMatrix();

  Vector3f GetUp();
  Vector3f GetDown();
  Vector3f GetForward();
  Vector3f GetBackward();
  Vector3f GetRight();
  Vector3f GetLeft();

  Vector3f GetPosition();
  Vector3f GetLocalPosition();
  Quaternion GetRotation();
  Quaternion GetLocalRotation();
  Vector3f GetScale();
  Vector3f GetLocalScale();

  void SetPosition(const float& x, const float& y, const float& z);
  void SetPosition(const Vector3f& v);
  void SetRotation(const float& x, const float& y, const float& z);
  void SetRotation(const Vector3f& v);
  void SetRotation(const Quaternion& q);
  void SetRotation(const Vector3f& v, const float& s);
  void SetRotationByDegrees(const float& x, const float& y, const float& z);
  void SetRotationByDegrees(const Vector3f v);
  void SetScale(const float& s);
  void SetScale(const float& x, const float& y, const float& z);
  void SetScale(const Vector3f& v);

  void Translate(const float& x, const float& y, const float& z);
  void Translate(const Vector3f& v);
  void Rotate(const float& x, const float& y, const float& z);
  void Rotate(const Vector3f& v);
  void Rotate(const Quaternion q);
  void RotateByDegrees(const float& x, const float& y, const float& z);
  void RotateByDegrees(const Vector3f v);
  void Scale(const float& value);
  void Scale(const float& x, const float& y, const float& z);
  void Scale(const Vector3f& v);

 private:
  Vector3f position_;
  Quaternion rotation_;
  Vector3f scale_;
};
}  // namespace voodoo

#endif