#include "../../stdafx.h"

#include "transform.h"
#include "game_object.h"
#include <d3d11.h>

namespace Nixie
{
	Transform::Transform(std::shared_ptr<GameObject> game_object) :
		game_object_(game_object),
		parent_(nullptr),
		position_(Vector3<float>(0.0f)),
		rotation_(Quaternion<float>(1, 0, 0, 0)),
		scale_(Vector3<float>(1.0f))
	{}


	Vector3<float> Transform::GetUp()
	{
		return rotation_.ToMatrix4() * Vector3<float>(0, 1, 0);
	}


	Vector3<float> Transform::GetDown()
	{
		return rotation_.ToMatrix4() * Vector3<float>(0, -1, 0);
	}


	Vector3<float> Transform::GetForward()
	{
		return rotation_.ToMatrix4() * Vector3<float>(0, 0, -1);
	}


	Vector3<float> Transform::GetBackward()
	{
		return rotation_.ToMatrix4() * Vector3<float>(0, 0, 1);
	}


	Vector3<float> Transform::GetRight()
	{
		return rotation_.ToMatrix4() * Vector3<float>(1, 0, 0);
	}


	Vector3<float> Transform::GetLeft()
	{
		return rotation_.ToMatrix4() * Vector3<float>(-1, 0, 0);
	}


	Matrix4x4<float> Transform::CalculateWorldMatrix()
	{
		auto name = game_object_->GetName();
		auto position = GetPosition();
		auto rotation = GetRotation();
		auto scale = GetScale();

		Matrix4x4<float> translation_matrix = Matrix4x4<float>::FromTranslationVector(position);
		Matrix4x4<float> rotation_matrix = rotation.ToMatrix4();
		Matrix4x4<float> scale_matrix = Matrix4x4<float>::FromScaleVector(scale);

		Matrix4x4<float> world_matrix = translation_matrix * rotation_matrix * scale_matrix;

		return world_matrix;
	}


	std::shared_ptr<Transform> Transform::GetParent()
	{
		return this->parent_;
	}


	void Transform::SetParent(std::shared_ptr<Transform> parent)
	{
		this->parent_ = parent;
	}


	Vector3<float> Transform::GetPosition()
	{
		return parent_ ? parent_->GetPosition() + position_ : position_;
	}


	Vector3<float> Transform::GetLocalPosition()
	{
		return position_;
	}


	Quaternion<float> Transform::GetRotation()
	{
		return parent_ ? parent_->GetRotation() * rotation_ : rotation_;
	}


	Quaternion<float> Transform::GetLocalRotation()
	{
		return rotation_;
	}


	Vector3<float> Transform::GetScale()
	{
		return parent_ ? parent_->GetScale() + scale_ : scale_;
	}


	Vector3<float> Transform::GetLocalScale()
	{
		return scale_;
	}


	void Transform::SetPosition(const float& x, const float& y, const float& z)
	{
		position_ = Vector3<float>(x, y, z);
	}


	void Transform::SetPosition(const Vector3<float>& v)
	{
		position_ = v;
	}


	void Transform::SetRotation(const float& x, const float& y, const float& z)
	{
		rotation_ = Quaternion<float>::FromEulerAngles(x, y, z);
	}


	void Transform::SetRotation(const Vector3<float>& v)
	{
		rotation_ = Quaternion<float>::FromEulerAngles(v);
	}


	void Transform::SetRotation(const Quaternion<float>& q)
	{
		rotation_ = q;
	}


	void Transform::SetRotation(const Vector3<float>& v, const float& s)
	{
		rotation_ = Quaternion<float>(v.x, v.y, v.z, s);
	}


	void Transform::SetRotationByDegrees(const float& x, const float& y, const float& z)
	{
		rotation_ = Quaternion<float>::FromEulerAngles(
			DegreeToRadian<float>(x),
			DegreeToRadian<float>(y),
			DegreeToRadian<float>(z)
		);
	}


	void Transform::SetRotationByDegrees(const Vector3<float> v)
	{
		rotation_ = Quaternion<float>::FromEulerAngles(
			DegreeToRadian<float>(v.x),
			DegreeToRadian<float>(v.y),
			DegreeToRadian<float>(v.z)
		);
	}


	void Transform::SetScale(const float& s)
	{
		scale_ = Vector3<float>(s);
	}


	void Transform::SetScale(const float& x, const float& y, const float& z)
	{
		scale_ = Vector3<float>(x, y, z);
	}


	void Transform::SetScale(const Vector3<float>& v)
	{
		scale_ = v;
	}


	void Transform::Translate(const float& x, const float& y, const float& z)
	{
		position_ += Vector3<float>(x, y, z);
	}


	void Transform::Translate(const Vector3<float>& v)
	{
		position_ += v;
	}


	void Transform::Rotate(const float& x, const float& y, const float& z)
	{
		rotation_ = rotation_ * Quaternion<float>::FromEulerAngles(x, y, z);
	}


	void Transform::Rotate(const Vector3<float>& v)
	{
		rotation_ = rotation_ * Quaternion<float>::FromEulerAngles(v);
	}


	void Transform::Rotate(const Quaternion<float> q)
	{
		rotation_ = rotation_ * q;
	}


	void Transform::RotateByDegrees(const float& x, const float& y, const float& z)
	{
		rotation_ = rotation_ * Quaternion<float>::FromEulerAngles(
			DegreeToRadian<float>(x),
			DegreeToRadian<float>(y),
			DegreeToRadian<float>(z)
		);
	}


	void Transform::RotateByDegrees(const Vector3<float> v)
	{
		rotation_ = rotation_ * Quaternion<float>::FromEulerAngles(
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
		scale_ += Vector3<float>(x, y, z);
	}


	void Transform::Scale(const Vector3<float>& v)
	{
		scale_ += v;
	}
}