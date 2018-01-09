#include "camera.h"

namespace Nixie
{
	void Camera::OnUpdate()
	{
	}

	void Camera::Render()
	{
		DirectX::SimpleMath::Vector3 up = DirectX::SimpleMath::Vector3::Up;
		DirectX::SimpleMath::Vector3 look_at = DirectX::SimpleMath::Vector3::Backward;
		DirectX::SimpleMath::Vector3 position = DirectX::SimpleMath::Vector3(
			position.x = GetPosition().x,
			position.y = GetPosition().y,
			position.z = GetPosition().z);

		DirectX::SimpleMath::Matrix rotation_matrix = DirectX::XMMatrixRotationQuaternion(
			DirectX::SimpleMath::Quaternion(
				GetRotation().x,
				GetRotation().y,
				GetRotation().z,
				GetRotation().w));

		up = DirectX::XMVector3TransformCoord(up, rotation_matrix);
		look_at = DirectX::XMVector3TransformCoord(look_at, rotation_matrix);
		look_at = DirectX::XMVectorAdd(position, look_at);

		view_matrix_ = DirectX::XMMatrixLookAtLH(position, look_at, up);
	}

	DirectX::SimpleMath::Matrix Camera::GetViewMatrix()
	{
		return view_matrix_;
	}
}