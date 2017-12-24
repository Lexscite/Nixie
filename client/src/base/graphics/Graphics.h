#ifndef GRAPHICS_H
#define GRAPHICS_H

#pragma once

#include "D3D.h"
#include "Camera.h"
#include "ColorShader.h"

class Graphics
{
public:
	static Graphics* GetSingleton();

	bool Init(UINT screen_width, UINT screen_height, bool vsync_enabled, bool fullscreen_enabled);
	void Release();
	bool Render();

private: 
	Graphics();

private:
	static Graphics* singleton_;
};

#endif