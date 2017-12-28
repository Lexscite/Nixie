#ifndef CAMERA_H
#define CAMERA_H

#pragma once

#include <directxmath.h>

#include "../../math/vector.h"
#include "../component.h"

using namespace DirectX;

class Camera : public Component
{
public:
	void Render();
	void GetViewMatrix(XMMATRIX&);

private:
	XMMATRIX view_matrix_;
};

#endif