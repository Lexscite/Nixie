#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "DirectX.h"

class CGraphics
{
public:
	static CGraphics* GetSingleton();

	bool Init(HWND hwnd, int clientWidth, int clientHeight, bool fullscreen);
	void Release();
	void Render();

private: 
	CGraphics();

private:
	static CGraphics* s_singleton;

	bool m_Fullscreen;
};

#endif