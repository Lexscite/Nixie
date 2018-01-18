#include "camera.h"

namespace Nixie
{
	void Camera::OnUpdate()
	{
	}

	void Camera::Render()
	{
		Vector3 position = GetTransform()->position;
		Quaternion rotation = GetTransform()->rotation;

		DirectX::SimpleMath::Vector3 dx_up = DirectX::SimpleMath::Vector3::Up;
		DirectX::SimpleMath::Vector3 dx_look_at = DirectX::SimpleMath::Vector3::Backward;
		DirectX::SimpleMath::Vector3 dx_position = DirectX::SimpleMath::Vector3(
			position.x,
			position.y,
			position.z);

		DirectX::SimpleMath::Matrix rotation_matrix = DirectX::XMMatrixRotationQuaternion(
			DirectX::SimpleMath::Quaternion(
				rotation.x,
				rotation.y,
				rotation.z,
				rotation.w));

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