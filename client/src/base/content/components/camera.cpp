#include "camera.h"

void Camera::OnUpdate()
{
	if (Input::IsKeyDown(Keyboard::Keys::W) && !Input::IsKeyDown(Keyboard::Keys::S))
		Translate(Vector3(0, 0, 2 * Time::GetDeltaTime()));

	if (Input::IsKeyDown(Keyboard::Keys::S) && !Input::IsKeyDown(Keyboard::Keys::W))
		Translate(Vector3(0, 0, -2 * Time::GetDeltaTime()));

	if (Input::IsKeyDown(Keyboard::Keys::D) && !Input::IsKeyDown(Keyboard::Keys::A))
		Translate(Vector3(2 * Time::GetDeltaTime(), 0, 0));

	if (Input::IsKeyDown(Keyboard::Keys::A) && !Input::IsKeyDown(Keyboard::Keys::D))
		Translate(Vector3(-2 * Time::GetDeltaTime(), 0, 0));
}

void Camera::Render()
{
	XMFLOAT3 up;
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	XMVECTOR up_vector = XMLoadFloat3(&up);

	XMFLOAT3 position;
	position.x = GetPosition().x;
	position.y = GetPosition().y;
	position.z = GetPosition().z;

	XMVECTOR position_vector = XMLoadFloat3(&position);

	XMFLOAT3 look_at;
	look_at.x = 0.0f;
	look_at.y = 0.0f;
	look_at.z = 1.0f;

	XMVECTOR look_at_vector = XMLoadFloat3(&look_at);

	float pitch = GetRotation().x * 0.0174532925f;
	float yaw = GetRotation().y * 0.0174532925f;
	float roll = GetRotation().z * 0.0174532925f;

	XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	up_vector = XMVector3TransformCoord(up_vector, rotationMatrix);
	look_at_vector = XMVector3TransformCoord(look_at_vector, rotationMatrix);
	look_at_vector = XMVectorAdd(position_vector, look_at_vector);

	view_matrix_ = XMMatrixLookAtLH(position_vector, look_at_vector, up_vector);
}

XMMATRIX Camera::GetViewMatrix()
{
	return view_matrix_;
}