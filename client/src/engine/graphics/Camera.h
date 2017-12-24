#ifndef CAMERA_H
#define CAMERA_H

#pragma once

#include <directxmath.h>

#include "../math//Vector.h"

using namespace DirectX;

class Camera
{
public:
	Camera();

	void Render();
	void GetViewMatrix(XMMATRIX&);

public:
	Vector3* position_;
	Vector3* rotation_;

private:
	XMMATRIX view_matrix_;
};

#endif