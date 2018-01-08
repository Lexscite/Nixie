#include "camera.h"

namespace Nixie
{
	void Camera::OnUpdate()
	{
		if (Input::IsKeyDown(DirectX::Keyboard::Keys::W) && !Input::IsKeyDown(DirectX::Keyboard::Keys::S))
			Translate(DirectX::SimpleMath::Vector3(0, 0, 2 * Time::GetDeltaTime()));

		if (Input::IsKeyDown(DirectX::Keyboard::Keys::S) && !Input::IsKeyDown(DirectX::Keyboard::Keys::W))
			Translate(DirectX::SimpleMath::Vector3(0, 0, -2 * Time::GetDeltaTime()));

		if (Input::IsKeyDown(DirectX::Keyboard::Keys::D) && !Input::IsKeyDown(DirectX::Keyboard::Keys::A))
			Translate(DirectX::SimpleMath::Vector3(2 * Time::GetDeltaTime(), 0, 0));

		if (Input::IsKeyDown(DirectX::Keyboard::Keys::A) && !Input::IsKeyDown(DirectX::Keyboard::Keys::D))
			Translate(DirectX::SimpleMath::Vector3(-2 * Time::GetDeltaTime(), 0, 0));
	}

	void Camera::Render()
	{
		DirectX::SimpleMath::Vector3 up = DirectX::SimpleMath::Vector3::Up;
		DirectX::SimpleMath::Vector3 look_at = DirectX::SimpleMath::Vector3(0, 0, 1);
		DirectX::SimpleMath::Vector3 position = DirectX::SimpleMath::Vector3(
			position.x = GetPosition().x,
			position.y = GetPosition().y,
			position.z = GetPosition().z);

		DirectX::SimpleMath::Matrix rotation_matrix = DirectX::XMMatrixRotationRollPitchYaw(
			GetRotation().x * 0.0174532925f,
			GetRotation().y * 0.0174532925f,
			GetRotation().z * 0.0174532925f);

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