#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#pragma once

#include "DirectX.h"

class CGraphics
{
public:
	static CGraphics* GetSingleton();

	bool Init(HWND hwnd, UINT screenWidth, UINT screenHeight, bool fullscreen);
	void Release();
	void Render();

private: 
	CGraphics();

private:
	static CGraphics* s_singleton;

	bool m_fullscreen;
};

#endif