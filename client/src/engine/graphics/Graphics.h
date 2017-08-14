#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#pragma once

#include "DirectX.h"

class CGraphics
{
public:
	static CGraphics* GetSingleton();

	bool Init(UINT screenWidth, UINT screenHeight, bool vsyncEnabled, bool fullscreenEnabled);
	void Release();
	void Render();

private: 
	CGraphics();

private:
	static CGraphics* s_singleton;

	bool m_vsyncEnabled;
	bool m_fullscreenEnabled;
};

#endif