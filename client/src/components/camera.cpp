#include "../stdafx_client.h"

#include "camera.h"

#include "math/quaternion.h"
#include "math/math.h"
#include "math/vector.h"
#include "math/matrix.h"


namespace nixie
{
	Camera::Camera() :
		view_matrix_(),
		projection_matrix_(),
		locked_(false),
		lock_point_(),
		fov_(mathfu::kPi / 4)
	{}


	bool Camera::OnUpdate()
	{
		CalculateViewMatrix();

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
		Vector3<float> pos = GetTransform()->GetPosition();
		Vector3<float> at;

		if (locked_)
		{
			at = lock_point_;
		}
		else
		{
			at = pos + GetTransform()->GetForward();
		}

		view_matrix_ = Matrix4x4<float>::LookAt(at, pos, GetTransform()->GetUp(), -1.0f);
	}


	Matrix4x4<float> Camera::GetViewMatrix()
	{
		return view_matrix_;
	}


	Matrix4x4<float> Camera::GetProjectionMatrix()
	{
		return projection_matrix_;
	}


	void Camera::LockOnPoint(const Vector3<float>& p)
	{
		lock_point_ = p; locked_ = true;
	}


	void Camera::LockOnGameObject(std::shared_ptr<GameObject> o)
	{
		lock_point_ = o->GetTransform()->GetPosition(); locked_ = true;
	}
}