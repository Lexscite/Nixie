#ifndef CAMERA_H
#define CAMERA_H

#pragma once

#include <directxmath.h>

#include "../component.h"

namespace Nixie
{
	class Camera : public Component
	{
	public:
		void Render();
		DirectX::SimpleMath::Matrix GetViewMatrix();

		virtual void OnUpdate() override;

	private:
		DirectX::SimpleMath::Matrix view_matrix_;
	};
}

#endif