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

float4x4 Transform::GetWorldMatrix() {
  float4x4 t = float4x4::FromTranslationVector(GetPosition());
  float4x4 r = GetRotation().ToMatrix4();
  float4x4 s = float4x4::FromScaleVector(GetScale());
  return t * r * s;
}

vec3f Transform::GetUp() {
  return rotation_.ToMatrix4() * kVec3fY;
}

vec3f Transform::GetDown() {
  return rotation_.ToMatrix4() * -kVec3fY;
}

vec3f Transform::GetForward() {
  return rotation_.ToMatrix4() * kVec3fZ;
}

vec3f Transform::GetBackward() {
  return rotation_.ToMatrix4() * -kVec3fZ;
}

vec3f Transform::GetRight() {
  return rotation_.ToMatrix4() * kVec3fX;
}

vec3f Transform::GetLeft() {
  return rotation_.ToMatrix4() * -kVec3fX;
}

// Position
vec3f Transform::GetPosition() {
  auto parent = GetParent();
  return parent ? parent->GetTransform()->GetPosition() + position_ : position_;
}

vec3f Transform::GetLocalPosition() {
  return position_;
}

void Transform::SetPosition(const float& x, const float& y, const float& z) {
  position_ = vec3f(x, y, z);
}

void Transform::SetPosition(const vec3f& v) {
  position_ = v;
}

void Transform::Translate(const float& x, const float& y, const float& z) {
  position_ += vec3f(x, y, z);
}

void Transform::Translate(const vec3f& v) {
  position_ += v;
}

// Rotation
quatf Transform::GetRotation() {
  auto parent = GetParent();
  return parent ? parent->GetTransform()->GetRotation() * rotation_ : rotation_;
}

quatf Transform::GetLocalRotation() {
  return rotation_;
}

void Transform::SetRotation(const float& x, const float& y, const float& z) {
  rotation_ = quatf::FromEulerAngles(x, y, z);
}

void Transform::SetRotation(const vec3f& v) {
  rotation_ = quatf::FromEulerAngles(v);
}

void Transform::SetRotation(const quatf& q) {
  rotation_ = q;
}

void Transform::SetRotation(const vec3f& v, const float& s) {
  rotation_ = quatf(s, v);
}

void Transform::SetRotationByDegrees(const float& x, const float& y, const float& z) {
  rotation_ = quatf::FromEulerAngles(dtorf(x), dtorf(y), dtorf(z));
}

void Transform::SetRotationByDegrees(const vec3f v) {
  rotation_ = quatf::FromEulerAngles(dtorv(v));
}

void Transform::Rotate(const float& x, const float& y, const float& z) {
  rotation_ = rotation_ * quatf::FromEulerAngles(x, y, z);
}

void Transform::Rotate(const vec3f& v) {
  rotation_ = rotation_ * quatf::FromEulerAngles(v);
}

void Transform::Rotate(const quatf q) {
  rotation_ = rotation_ * q;
}

void Transform::RotateByDegrees(const float& x, const float& y, const float& z) {
  rotation_ = rotation_ * quatf::FromEulerAngles(dtorf(x), dtorf(y), dtorf(z));
}

void Transform::RotateByDegrees(const vec3f v) {
  rotation_ = rotation_ * quatf::FromEulerAngles(dtorv(v));
}

// Scale
vec3f Transform::GetScale() {
  auto parent = GetParent();
  return parent ? parent->GetTransform()->GetScale() + scale_ : scale_;
}

vec3f Transform::GetLocalScale() {
  return scale_;
}

void Transform::SetScale(const float& s) {
  scale_ = vec3f(s);
}

void Transform::SetScale(const float& x, const float& y, const float& z) {
  scale_ = vec3f(x, y, z);
}

void Transform::SetScale(const vec3f& v) {
  scale_ = v;
}

void Transform::Scale(const float& value) {
  scale_ += value;
}

void Transform::Scale(const float& x, const float& y, const float& z) {
  scale_ += vec3f(x, y, z);
}

void Transform::Scale(const vec3f& v) {
  scale_ += v;
}
}  // namespace voodoo