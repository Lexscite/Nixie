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

	bool Init(UINT screenWidth, UINT screenHeight, bool vsyncEnabled, bool fullscreenEnabled);
	void Release();
	void Render();

private: 
	Graphics();

private:
	static Graphics* s_singleton;

	bool m_vsyncEnabled;
	bool m_fullscreenEnabled;

	Camera* m_pCamera;
	ColorShader* m_pColorShader;
};

#endif