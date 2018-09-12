#ifndef NIXIE_CAMERA_H_
#define NIXIE_CAMERA_H_

#pragma once

#include "../component.h"

namespace Nixie
{
	class Camera : public Component
	{
	public:
		Camera() : fov_(mathfu::kPi / 4) {}

		void CalculateViewMatrix();
		Matrix4x4<float> GetViewMatrix();
		Matrix4x4<float> GetProjectionMatrix();

		void LockOnPoint(const Vector3<float>& p) { lock_point_ = p; locked_ = true; }
		void LockOnGameObject(std::shared_ptr<GameObject> o) { lock_point_ = o->GetTransform()->GetPosition(); locked_ = true; }
		void Unlock() { locked_ = false; }

	private:
		virtual bool OnInit() override;
		virtual bool OnUpdate() override;

	private:
		Matrix4x4<float> view_matrix_;
		Matrix4x4<float> projection_matrix_;

		bool locked_;
		Vector3<float> lock_point_;

		float fov_;
	};
}

#endif