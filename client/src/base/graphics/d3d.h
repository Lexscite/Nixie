#ifndef DIRECTX_H
#define DIRECTX_H

#pragma once

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11.h>
#include <d3dcompiler.h>

#include "SimpleMath.h"
#include "WICTextureLoader.h"

#include "../utils/memory.h"
#include "../utils/debug.h"
#include "../math/math.h"

namespace Nixie
{
	class D3D final
	{
	public:
		static D3D* GetSingleton();

		bool Init(
			unsigned int screen_width,
			unsigned int screen_height,
			bool vsync_enabled,
			bool fullscreen_enabled,
			float screen_depth,
			float screen_near);
		void Release();

		void BeginScene(Color clear_color);
		void EndScene();

		bool SetRasterizer();

		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetDeviceContext();

		DirectX::SimpleMath::Matrix GetProjectionMatrix();
		DirectX::SimpleMath::Matrix GetOrthoMatrix();

		void ToggleWireframeMode();

	private:
		D3D();

	private:
		static D3D* singleton;

		bool vsync_enabled;
		bool fullscreen_enabled;
		bool msaa_enabled;
		bool wireframe_mode_enabled;

		ID3D11Device* device;
		ID3D11DeviceContext* device_context;
		IDXGISwapChain* swap_chain;
		D3D_FEATURE_LEVEL feature_level;

		UINT adapter_memory;
		char adapter_desc[128];

		ID3D11RenderTargetView* render_target_view;
		ID3D11Texture2D* depth_stencil_buffer;
		ID3D11DepthStencilState* depth_stencil_state;
		ID3D11DepthStencilView* depth_stencil_view;
		ID3D11RasterizerState* rasterizer_state;

		DirectX::SimpleMath::Matrix projection_matrix;
		DirectX::SimpleMath::Matrix ortho_matrix;
	};
}

#endif