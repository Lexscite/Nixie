#include "../stdafx_core.h"
#include "transform.h"

#include "game_object.h"


namespace vodoo
{
	Transform::Transform(std::shared_ptr<GameObject> game_object) :
		game_object_(game_object),
		parent_(nullptr),
		position_(Vector3f(0.0f)),
		rotation_(Quaternion(1, 0, 0, 0)),
		scale_(Vector3f(1.0f))
	{}

	std::shared_ptr<Transform> Transform::GetParent()
	{
		return this->parent_;
	}

	void Transform::SetParent(std::shared_ptr<Transform> parent)
	{
		this->parent_ = parent;
	}

	Matrix4x4f Transform::CalculateWorldMatrix()
	{
		auto name = game_object_->GetName();
		auto position = GetPosition();
		auto rotation = GetRotation();
		auto scale = GetScale();

		Matrix4x4f translation_matrix = Matrix4x4f::FromTranslationVector(position);
		Matrix4x4f rotation_matrix = rotation.ToMatrix4();
		Matrix4x4f scale_matrix = Matrix4x4f::FromScaleVector(scale);

		Matrix4x4f world_matrix = translation_matrix * rotation_matrix * scale_matrix;

		return world_matrix;
	}

	Vector3f Transform::GetUp()
	{
		return rotation_.ToMatrix4() * Vector3f(0, 1, 0);
	}

	Vector3f Transform::GetDown()
	{
		return rotation_.ToMatrix4() * Vector3f(0, -1, 0);
	}

	Vector3f Transform::GetForward()
	{
		return rotation_.ToMatrix4() * Vector3f(0, 0, -1);
	}

	Vector3f Transform::GetBackward()
	{
		return rotation_.ToMatrix4() * Vector3f(0, 0, 1);
	}

	Vector3f Transform::GetRight()
	{
		return rotation_.ToMatrix4() * Vector3f(1, 0, 0);
	}

	Vector3f Transform::GetLeft()
	{
		return rotation_.ToMatrix4() * Vector3f(-1, 0, 0);
	}

	Vector3f Transform::GetPosition()
	{
		return parent_ ? parent_->GetPosition() + position_ : position_;
	}

	Vector3f Transform::GetLocalPosition()
	{
		return position_;
	}

	Quaternion Transform::GetRotation()
	{
		return parent_ ? parent_->GetRotation() * rotation_ : rotation_;
	}

	Quaternion Transform::GetLocalRotation()
	{
		return rotation_;
	}

	Vector3f Transform::GetScale()
	{
		return parent_ ? parent_->GetScale() + scale_ : scale_;
	}

	Vector3f Transform::GetLocalScale()
	{
		return scale_;
	}

	void Transform::SetPosition(const float& x, const float& y, const float& z)
	{
		position_ = Vector3f(x, y, z);
	}

	void Transform::SetPosition(const Vector3f& v)
	{
		position_ = v;
	}

	void Transform::SetRotation(const float& x, const float& y, const float& z)
	{
		rotation_ = Quaternion::FromEulerAngles(x, y, z);
	}

	void Transform::SetRotation(const Vector3f& v)
	{
		rotation_ = Quaternion::FromEulerAngles(v);
	}

	void Transform::SetRotation(const Quaternion& q)
	{
		rotation_ = q;
	}

	void Transform::SetRotation(const Vector3f& v, const float& s)
	{
		rotation_ = Quaternion(v.x, v.y, v.z, s);
	}

	void Transform::SetRotationByDegrees(const float& x, const float& y, const float& z)
	{
		rotation_ = Quaternion::FromEulerAngles(
			DegreeToRadian<float>(x),
			DegreeToRadian<float>(y),
			DegreeToRadian<float>(z)
		);
	}

	void Transform::SetRotationByDegrees(const Vector3f v)
	{
		rotation_ = Quaternion::FromEulerAngles(
			DegreeToRadian<float>(v.x),
			DegreeToRadian<float>(v.y),
			DegreeToRadian<float>(v.z)
		);
	}

	void Transform::SetScale(const float& s)
	{
		scale_ = Vector3f(s);
	}

	void Transform::SetScale(const float& x, const float& y, const float& z)
	{
		scale_ = Vector3f(x, y, z);
	}

	void Transform::SetScale(const Vector3f& v)
	{
		scale_ = v;
	}

	void Transform::Translate(const float& x, const float& y, const float& z)
	{
		position_ += Vector3f(x, y, z);
	}

	void Transform::Translate(const Vector3f& v)
	{
		position_ += v;
	}

	void Transform::Rotate(const float& x, const float& y, const float& z)
	{
		rotation_ = rotation_ * Quaternion::FromEulerAngles(x, y, z);
	}

	void Transform::Rotate(const Vector3f& v)
	{
		rotation_ = rotation_ * Quaternion::FromEulerAngles(v);
	}

	void Transform::Rotate(const Quaternion q)
	{
		rotation_ = rotation_ * q;
	}

	void Transform::RotateByDegrees(const float& x, const float& y, const float& z)
	{
		rotation_ = rotation_ * Quaternion::FromEulerAngles(
			DegreeToRadian<float>(x),
			DegreeToRadian<float>(y),
			DegreeToRadian<float>(z)
		);
	}

	void Transform::RotateByDegrees(const Vector3f v)
	{
		rotation_ = rotation_ * Quaternion::FromEulerAngles(
			DegreeToRadian<float>(v.x),
			DegreeToRadian<float>(v.y),
			DegreeToRadian<float>(v.z)
		);
	}

	void Transform::Scale(const float& value)
	{
		scale_ += value;
	}

	void Transform::Scale(const float& x, const float& y, const float& z)
	{
		scale_ += Vector3f(x, y, z);
	}

	void Transform::Scale(const Vector3f& v)
	{
		scale_ += v;
	}
}