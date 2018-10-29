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

#include "../include/voodoo/transform.h"

namespace voodoo {
Transform::Transform()
    : position_(kVec3fZeros),
      rotation_(kQuatfIdentity),
      scale_(kVec3fOnes) {}

bool Transform::HasChanged() {
  return changed_;
}

float4x4 Transform::GetWorldMatrix() {
  if (changed_) {
    CalculateWorldMatrix();
  }
  return world_matrix_;
}

vec3f Transform::GetUp() const {
  return rotation_.ToMatrix4() * kVec3fY;
}

vec3f Transform::GetDown() const {
  return rotation_.ToMatrix4() * -kVec3fY;
}

vec3f Transform::GetForward() const {
  return rotation_.ToMatrix4() * kVec3fZ;
}

vec3f Transform::GetBackward() const {
  return rotation_.ToMatrix4() * -kVec3fZ;
}

vec3f Transform::GetRight() const {
  return rotation_.ToMatrix4() * kVec3fX;
}

vec3f Transform::GetLeft() const {
  return rotation_.ToMatrix4() * -kVec3fX;
}

// Position
vec3f Transform::GetPosition() const {
  auto parent = GetParent();
  return parent ? parent->GetTransform()->GetPosition() + position_ : position_;
}

vec3f Transform::GetLocalPosition() const {
  return position_;
}

void Transform::SetPosition(const float& x, const float& y, const float& z) {
  changed_ = true;
  position_ = vec3f(x, y, z);
}

void Transform::SetPosition(const vec3f& v) {
  changed_ = true;
  position_ = v;
}

void Transform::Translate(const float& x, const float& y, const float& z) {
  changed_ = true;
  position_ += vec3f(x, y, z);
}

void Transform::Translate(const vec3f& v) {
  changed_ = true;
  position_ += v;
}

// Rotation
quatf Transform::GetRotation() const {
  auto parent = GetParent();
  return parent ? parent->GetTransform()->GetRotation() * rotation_ : rotation_;
}

quatf Transform::GetLocalRotation() const {
  return rotation_;
}

void Transform::SetRotation(const float& x, const float& y, const float& z) {
  changed_ = true;
  rotation_ = quatf::FromEulerAngles(x, y, z);
}

void Transform::SetRotation(const vec3f& v) {
  changed_ = true;
  rotation_ = quatf::FromEulerAngles(v);
}

void Transform::SetRotation(const quatf& q) {
  changed_ = true;
  rotation_ = q;
}

void Transform::SetRotation(const vec3f& v, const float& s) {
  changed_ = true;
  rotation_ = quatf(s, v);
}

void Transform::SetRotationByDegrees(const float& x, const float& y, const float& z) {
  changed_ = true;
  rotation_ = quatf::FromEulerAngles(dtorf(x), dtorf(y), dtorf(z));
}

void Transform::SetRotationByDegrees(const vec3f v) {
  changed_ = true;
  rotation_ = quatf::FromEulerAngles(dtorv(v));
}

void Transform::Rotate(const float& x, const float& y, const float& z) {
  changed_ = true;
  rotation_ = rotation_ * quatf::FromEulerAngles(x, y, z);
}

void Transform::Rotate(const vec3f& v) {
  changed_ = true;
  rotation_ = rotation_ * quatf::FromEulerAngles(v);
}

void Transform::Rotate(const quatf q) {
  changed_ = true;
  rotation_ = rotation_ * q;
}

void Transform::RotateByDegrees(const float& x, const float& y, const float& z) {
  changed_ = true;
  rotation_ = rotation_ * quatf::FromEulerAngles(dtorf(x), dtorf(y), dtorf(z));
}

void Transform::RotateByDegrees(const vec3f v) {
  changed_ = true;
  rotation_ = rotation_ * quatf::FromEulerAngles(dtorv(v));
}

// Scale
vec3f Transform::GetScale() const {
  auto parent = GetParent();
  return parent ? parent->GetTransform()->GetScale() + scale_ : scale_;
}

vec3f Transform::GetLocalScale() const {
  return scale_;
}

void Transform::SetScale(const float& s) {
  scale_ = vec3f(s);
}

void Transform::SetScale(const float& x, const float& y, const float& z) {
  changed_ = true;
  scale_ = vec3f(x, y, z);
}

void Transform::SetScale(const vec3f& v) {
  changed_ = true;
  scale_ = v;
}

void Transform::Scale(const float& value) {
  changed_ = true;
  scale_ += value;
}

void Transform::Scale(const float& x, const float& y, const float& z) {
  changed_ = true;
  scale_ += vec3f(x, y, z);
}

void Transform::Scale(const vec3f& v) {
  changed_ = true;
  scale_ += v;
}

void Transform::CalculateWorldMatrix() {
  float4x4 t = float4x4::FromTranslationVector(GetPosition());
  float4x4 r = GetRotation().ToMatrix4();
  float4x4 s = float4x4::FromScaleVector(GetScale());
  world_matrix_ = t * r * s;
}
}  // namespace voodoo