#ifndef __DIRECTX_H__
#define __DIRECTX_H__

#pragma once

#include <dxgi.h>
#include <d3d11.h>

#include "..\utils\Memory.h"
#include "..\utils\Debug.h"

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")

class CDirectX
{
public:
	static CDirectX* GetSingleton();

	bool Init(UINT screenWidth, UINT screenHeight, bool vsyncEnabled, bool fullscreenEnabled);
	void Release();

private:
	CDirectX();

private:
	static CDirectX* s_singleton;

	UINT m_screenWidth;
	UINT m_screenHeight;
	bool m_vsyncEnabled;
	bool m_fullscreenEnabled;

	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;
	IDXGISwapChain* m_pSwapChain;
	D3D_FEATURE_LEVEL m_featureLevel;
};

#endif