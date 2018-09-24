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

		Matrix4x4f GetViewMatrix();
		Matrix4x4f GetProjectionMatrix();

	private:
		virtual bool OnInit() override;
		virtual bool OnUpdate() override;

		void CalculateViewMatrix();
		void CalculateProjectionMatrix();

	private:
		float fov_, aspect_ratio_, z_near_, z_far_;
		
		Matrix4x4f view_matrix_;
		Matrix4x4f projection_matrix_;
	};
}

#endif