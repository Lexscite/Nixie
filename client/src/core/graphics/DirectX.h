#ifndef DIRECTX_H
#define DIRECTX_H

#include <iostream>
#include <d3d11.h>
#include <DirectXColors.h>

#pragma comment(lib, "d3d11.lib")

using namespace DirectX;

using std::cout;
using std::cerr;
using std::endl;

namespace NXGraphics
{
	class DirectX
	{
	public:
		DirectX();
		~DirectX();

		bool Init(HWND hwnd, int clientWidth, int clientHeight, bool vsync, bool fullscreen, float depth, float nearClip);
		void Render();

	protected:
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pImmediateContext;
		IDXGISwapChain* m_pSwapChain;
		ID3D11RenderTargetView* m_pRenderTargetView;

		D3D_DRIVER_TYPE m_DriverType;
		D3D_FEATURE_LEVEL m_FeatureLevel;
		D3D11_VIEWPORT m_Viewport;
	};
}

#endif // !DIRECTX_H