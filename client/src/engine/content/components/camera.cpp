#include "../../../stdafx.h"

#include "camera.h"


namespace Nixie
{
	void Camera::CalculateWorldMatrix()
	{
		Vector3<float> position = GetTransform()->GetPosition();
		Quaternion rotation = GetTransform()->GetRotation();

		auto dx_up = DirectX::SimpleMath::Vector3::Up;
		auto dx_look_at = DirectX::SimpleMath::Vector3::Backward;
		auto dx_position = DirectX::SimpleMath::Vector3(position.x, position.y, position.z);
		auto dx_rotation = DirectX::SimpleMath::Quaternion(rotation.v.x, rotation.v.y, rotation.v.z, rotation.w);
		auto rotation_matrix = DirectX::XMMatrixRotationQuaternion(dx_rotation);

		dx_up = DirectX::XMVector3TransformCoord(dx_up, rotation_matrix);
		dx_look_at = DirectX::XMVector3TransformCoord(dx_look_at, rotation_matrix);
		dx_look_at = DirectX::XMVectorAdd(dx_position, dx_look_at);

		view_matrix_ = DirectX::XMMatrixLookAtLH(dx_position, dx_look_at, dx_up);
	}


	DirectX::SimpleMath::Matrix Camera::GetViewMatrix()
	{
		return view_matrix_;
	}
}