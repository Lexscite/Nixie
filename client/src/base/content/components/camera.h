#ifndef CAMERA_H
#define CAMERA_H

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