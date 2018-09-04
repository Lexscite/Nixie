#include "../../stdafx.h"

#include "transform.h"
#include "../graphics/d3d.h"


namespace Nixie
{
	DirectX::SimpleMath::Matrix Transform::CalculateWorldMatrix()
	{
		Vector3 position = GetPosition();
		Quaternion rotation = GetRotation();
		Vector3 scale = GetScale();

		auto dx_position = DirectX::SimpleMath::Vector3(position.x, position.y, position.z);
		auto dx_rotation = DirectX::SimpleMath::Quaternion(rotation.x, rotation.y, rotation.z, rotation.w);
		auto dx_scale = DirectX::SimpleMath::Vector3(scale.x, scale.y, scale.z);

		auto translation_matrix = DirectX::SimpleMath::Matrix::CreateTranslation(dx_position);
		auto rotation_matrix = DirectX::SimpleMath::Matrix::CreateFromQuaternion(dx_rotation);
		auto scaling_matrix = DirectX::SimpleMath::Matrix::CreateScale(dx_scale);

		return scaling_matrix * rotation_matrix * translation_matrix;
	}


	std::shared_ptr<Transform> Transform::GetParent()
	{
		return this->parent_;
	}


	void Transform::SetParent(std::shared_ptr<Transform> parent)
	{
		this->parent_ = parent;
	}


	Vector3 Transform::GetPosition()
	{
		return parent_ ? parent_->GetPosition() + position_ : position_;
	}


	Vector3 Transform::GetLocalPosition()
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


	Vector3 Transform::GetScale()
	{
		return parent_ ? parent_->GetScale() * scale_ : scale_;
	}


	Vector3 Transform::GetLocalScale()
	{
		return scale_;
	}
}