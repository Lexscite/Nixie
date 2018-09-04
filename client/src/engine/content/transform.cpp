#include "../../stdafx.h"

#include "transform.h"

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

	Transform* Transform::GetParent()
	{
		return this->parent;
	}

	void Transform::SetParent(Transform* parent)
	{
		this->parent = parent;
	}

	Vector3 Transform::GetPosition()
	{
		return parent ? parent->GetPosition() + position : position;
	}

	Vector3 Transform::GetLocalPosition()
	{
		return position;
	}

	Quaternion Transform::GetRotation()
	{
		return parent ? parent->GetRotation() * rotation : rotation;
	}

	Quaternion Transform::GetLocalRotation()
	{
		return rotation;
	}

	Vector3 Transform::GetScale()
	{
		return parent ? parent->GetScale() * scale : scale;
	}

	Vector3 Transform::GetLocalScale()
	{
		return scale;
	}
}