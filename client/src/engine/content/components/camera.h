#ifndef NIXIE_CAMERA_H_
#define NIXIE_CAMERA_H_

#pragma once

#include "../component.h"

namespace Nixie
{
	class Camera : public Component
	{
	public:
		void Render();
		DirectX::SimpleMath::Matrix GetViewMatrix();

	private:
		DirectX::SimpleMath::Matrix view_matrix;
	};
}

#endif