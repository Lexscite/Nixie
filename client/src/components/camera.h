#ifndef NIXIE_CAMERA_H_
#define NIXIE_CAMERA_H_

#pragma once

#include "core/component.h"


namespace nixie
{
	class Camera : public Component
	{
	public:
		Camera();

		void CalculateViewMatrix();
		Matrix4x4<float> GetViewMatrix();
		Matrix4x4<float> GetProjectionMatrix();

		void LockOnPoint(const Vector3<float>& p);
		void LockOnGameObject(std::shared_ptr<GameObject> o);
		void Unlock() { locked_ = false; }

	private:
		virtual bool OnInit() override;
		virtual bool OnUpdate() override;

	private:
		float fov_, aspect_ratio_, z_near_, z_far_;
		
		Matrix4x4<float> view_matrix_;
		Matrix4x4<float> projection_matrix_;

		bool locked_;
		Vector3<float> lock_point_;
	};
}

#endif