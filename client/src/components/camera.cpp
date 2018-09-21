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
		projection_matrix_(),
		locked_(false),
		lock_point_()
	{}


	bool Camera::OnUpdate()
	{
		CalculateViewMatrix();

		return true;
	}


	bool Camera::OnInit()
	{
		projection_matrix_ = Matrix4x4<float>::Perspective(fov_, aspect_ratio_, z_near_, z_far_, -1.0f);

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