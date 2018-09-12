#include "../../../stdafx.h"

#include "camera.h"
#include "../../math/quaternion.h"


namespace Nixie
{
	bool Camera::OnUpdate()
	{
		return true;
	}


	bool Camera::OnInit()
	{
		float screen_w = 800.0f;
		float screen_h = 600.0f;
		float aspect_ratio = screen_w / screen_h;
		float znear = 0.1f, zfar = 1000.0f;

		projection_matrix_ = Matrix4x4<float>::Perspective(fov_, aspect_ratio, znear, zfar, -1.0f);

		CalculateViewMatrix();

		return true;
	}


	void Camera::CalculateViewMatrix()
	{
		Vector3<float> eye_pos = GetTransform()->GetPosition();
		Vector3<float> at;
		if (locked_)
		{
			at = lock_point_;
		}
		else
		{
			at = eye_pos + GetTransform()->GetBackward();
		}

		view_matrix_ = Matrix4x4<float>::LookAt(at, eye_pos, GetTransform()->GetUp(), -1.0f);
	}


	Matrix4x4<float> Camera::GetViewMatrix()
	{
		return view_matrix_;
	}


	Matrix4x4<float> Camera::GetProjectionMatrix()
	{
		return projection_matrix_;
	}
}