// This file is part of Voodoo Engine.
//
// Voodoo Engine is free software : you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Voodoo Engine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Foobar.  If not, see <https://www.gnu.org/licenses/>.

#include "../include/voodoo/camera.h"
#include "../include/voodoo/quaternion.h"
#include "../include/voodoo/vector.h"
#include "../include/voodoo/matrix.h"
#include "../include/voodoo/math.h"

namespace voodoo
{
	Camera::Camera() :
		fov_(math::pi / 4),
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
		projection_matrix_ = Matrix4x4f::Perspective(fov_, aspect_ratio_,
                                                 z_near_, z_far_, -1.0f);
	}

	Matrix4x4f Camera::GetViewMatrix()
	{
		return view_matrix_;
	}

	Matrix4x4f Camera::GetProjectionMatrix()
	{
		return projection_matrix_;
	}
}  // namespace voodoo