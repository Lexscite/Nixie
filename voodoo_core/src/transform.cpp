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
Transform::Transform() : position_(Vector3f(0.0f)),
                         rotation_(Quaternion(1, 0, 0, 0)),
                         scale_(Vector3f(1.0f)) {}

Matrix4x4f Transform::GetWorldMatrix() {
  auto name = game_object_->GetName();
  auto position = GetPosition();
  auto rotation = GetRotation();
  auto scale = GetScale();

  Matrix4x4f translation_matrix = Matrix4x4f::FromTranslationVector(position);
  Matrix4x4f rotation_matrix = rotation.ToMatrix4();
  Matrix4x4f scale_matrix = Matrix4x4f::FromScaleVector(scale);

  return translation_matrix * rotation_matrix * scale_matrix;
}

Vector3f Transform::GetUp() {
  return rotation_.ToMatrix4() * Vector3f(0, 1, 0);
}

Vector3f Transform::GetDown() {
  return rotation_.ToMatrix4() * Vector3f(0, -1, 0);
}

Vector3f Transform::GetForward() {
  return rotation_.ToMatrix4() * Vector3f(0, 0, 1);
}

Vector3f Transform::GetBackward() {
  return rotation_.ToMatrix4() * Vector3f(0, 0, -1);
}

Vector3f Transform::GetRight() {
  return rotation_.ToMatrix4() * Vector3f(1, 0, 0);
}

Vector3f Transform::GetLeft() {
  return rotation_.ToMatrix4() * Vector3f(-1, 0, 0);
}

Vector3f Transform::GetPosition() {
  auto p = GetParent();
  return p ? p->GetTransform()->GetPosition() + position_ : position_;
}

Vector3f Transform::GetLocalPosition() {
  return position_;
}

Quaternion Transform::GetRotation() {
  auto p = GetParent();
  return p ? p->GetTransform()->GetRotation() * rotation_ : rotation_;
}

Quaternion Transform::GetLocalRotation() {
  return rotation_;
}

Vector3f Transform::GetScale() {
  auto p = GetParent();
  return p ? p->GetTransform()->GetScale() + scale_ : scale_;
}

Vector3f Transform::GetLocalScale() {
  return scale_;
}

void Transform::SetPosition(const float& x, const float& y, const float& z) {
  position_ = Vector3f(x, y, z);
}

void Transform::SetPosition(const Vector3f& v) {
  position_ = v;
}

void Transform::SetRotation(const float& x, const float& y, const float& z) {
  rotation_ = Quaternion::FromEulerAngles(x, y, z);
}

void Transform::SetRotation(const Vector3f& v) {
  rotation_ = Quaternion::FromEulerAngles(v);
}

void Transform::SetRotation(const Quaternion& q) {
  rotation_ = q;
}

void Transform::SetRotation(const Vector3f& v, const float& s) {
  rotation_ = Quaternion(s, v);
}

void Transform::SetRotationByDegrees(const float& x, const float& y,
                                     const float& z) {
  auto q = Quaternion::FromEulerAngles(dtorf(x), dtorf(y), dtorf(z));
  rotation_ = q;
}

void Transform::SetRotationByDegrees(const Vector3f v) {
  auto q = Quaternion::FromEulerAngles(dtorv(v));
  rotation_ = q;
}

void Transform::SetScale(const float& s) { scale_ = Vector3f(s); }

void Transform::SetScale(const float& x, const float& y, const float& z) {
  scale_ = Vector3f(x, y, z);
}

void Transform::SetScale(const Vector3f& v) {
  scale_ = v;
}

void Transform::Translate(const float& x, const float& y, const float& z) {
  position_ += Vector3f(x, y, z);
}

void Transform::Translate(const Vector3f& v) {
  position_ += v;
}

void Transform::Rotate(const float& x, const float& y, const float& z) {
  rotation_ = rotation_ * Quaternion::FromEulerAngles(x, y, z);
}

void Transform::Rotate(const Vector3f& v) {
  rotation_ = rotation_ * Quaternion::FromEulerAngles(v);
}

void Transform::Rotate(const Quaternion q) {
  rotation_ = rotation_ * q;
}

void Transform::RotateByDegrees(const float& x, const float& y, const float& z) {
  auto q = Quaternion::FromEulerAngles(dtorf(x), dtorf(y), dtorf(z));
  rotation_ = rotation_ * q;
}

void Transform::RotateByDegrees(const Vector3f v) {
  auto q = Quaternion::FromEulerAngles(dtorv(v));
  rotation_ = rotation_ * q;
}

void Transform::Scale(const float& value) {
  scale_ += value;
}

void Transform::Scale(const float& x, const float& y, const float& z) {
  scale_ += Vector3f(x, y, z);
}

void Transform::Scale(const Vector3f& v) {
  scale_ += v;
}
}  // namespace voodoo