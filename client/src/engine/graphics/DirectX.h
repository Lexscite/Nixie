#ifndef __DIRECTX_H__
#define __DIRECTX_H__

#pragma once

#include <d3d11.h>
#include <directxmath.h>

#include "..\utils\Memory.h"
#include "..\utils\Debug.h"
#include "..\math\Color.h"

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

class CDirectX
{
public:
	static CDirectX* GetSingleton();

	bool Init(UINT screenWidth, UINT screenHeight, bool vsyncEnabled, bool fullscreenEnabled, float screenDepth, float screenNear);
	void Release();

	void BeginScene(Color* clearColor);
	void EndScene();

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

	UINT m_adapterMemory;
	char m_pAdapterDesc[128];

	ID3D11RenderTargetView* m_pRenderTargetView;
	ID3D11Texture2D* m_pDepthStencilBuffer;
	ID3D11DepthStencilState* m_pDepthStencilState;
	ID3D11DepthStencilView* m_pDepthStencilView;
	ID3D11RasterizerState* m_pRasterizerState;

	XMMATRIX m_projectionMatrix;
	XMMATRIX m_worldMatrix;
	XMMATRIX m_orthoMatrix;
};

#endif