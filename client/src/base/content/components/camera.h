#ifndef CAMERA_H
#define CAMERA_H

#pragma once

#include <directxmath.h>

#include "../component.h"

using namespace DirectX;

class Camera : public Component
{
public:
	void Render();
	XMMATRIX GetViewMatrix();

private:
	XMMATRIX view_matrix_;
};

#endif