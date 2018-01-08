#ifndef CAMERA_H
#define CAMERA_H

#pragma once

#include <directxmath.h>

#include "../component.h"

using namespace DirectX;

namespace Nixie
{
	class Camera : public Component
	{
	public:
		void Render();
		XMMATRIX GetViewMatrix();

		virtual void OnUpdate() override;

	private:
		XMMATRIX view_matrix_;
	};
}

#endif