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

  bool HasChanged();

  float4x4 GetWorldMatrix();

  vec3f GetUp();
  vec3f GetDown();
  vec3f GetForward();
  vec3f GetBackward();
  vec3f GetRight();
  vec3f GetLeft();

  vec3f GetPosition() const;
  vec3f GetLocalPosition() const;
  void SetPosition(const float& x, const float& y, const float& z);
  void SetPosition(const vec3f& v);
  void Translate(const float& x, const float& y, const float& z);
  void Translate(const vec3f& v);

  quatf GetRotation() const;
  quatf GetLocalRotation() const;
  void SetRotation(const float& x, const float& y, const float& z);
  void SetRotation(const vec3f& v);
  void SetRotation(const quatf& q);
  void SetRotation(const vec3f& v, const float& s);
  void SetRotationByDegrees(const float& x, const float& y, const float& z);
  void SetRotationByDegrees(const vec3f v);
  void Rotate(const float& x, const float& y, const float& z);
  void Rotate(const vec3f& v);
  void Rotate(const quatf q);
  void RotateByDegrees(const float& x, const float& y, const float& z);
  void RotateByDegrees(const vec3f v);

  vec3f GetScale() const;
  vec3f GetLocalScale() const;
  void SetScale(const float& s);
  void SetScale(const float& x, const float& y, const float& z);
  void SetScale(const vec3f& v);
  void Scale(const float& value);
  void Scale(const float& x, const float& y, const float& z);
  void Scale(const vec3f& v);

 private:
  void CalculateWorldMatrix();

 private:
  float4x4 world_matrix_;

  vec3f position_;
  quatf rotation_;
  vec3f scale_;

  bool changed_;
};
}  // namespace voodoo

#endif