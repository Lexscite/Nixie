#include "../stdafx_client.h"
#include "camera.h"

#include "math/quaternion.h"
#include "math/math.h"
#include "math/vector.h"
#include "math/matrix.h"

namespace nixie
{
	Camera::Camera() :
		fov_(mathfu::kPi / 4),
		aspect_ratio_(8.0f / 6.0f),
		z_near_(0.1f),
		z_far_(1000.0f),
		view_matrix_(),
		projection_matrix_()
	{}

	bool Camera::OnUpdate()
	{
		CalculateViewMatrix();

		return true;
	}

	bool Camera::OnInit()
	{
		CalculateViewMatrix();
		CalculateProjectionMatrix();

		return true;
	}

	void Camera::CalculateViewMatrix()
	{
		Vector3f pos = GetTransform()->GetPosition();
		Vector3f at = pos + GetTransform()->GetForward();
		Vector3f up = GetTransform()->GetUp();

		view_matrix_ = Matrix4x4f::LookAt(at, pos, up, -1.0f);
	}

	void Camera::CalculateProjectionMatrix()
	{
		projection_matrix_ = Matrix4x4f::Perspective(fov_, aspect_ratio_, z_near_, z_far_, -1.0f);
	}

	Matrix4x4f Camera::GetViewMatrix()
	{
		return view_matrix_;
	}

	Matrix4x4f Camera::GetProjectionMatrix()
	{
		return projection_matrix_;
	}
}