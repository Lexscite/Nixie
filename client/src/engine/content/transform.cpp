#include "../../stdafx.h"

#include "transform.h"
#include "game_object.h"
#include <d3d11.h>
#include "SimpleMath.h"

namespace Nixie
{
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
}