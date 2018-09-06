#ifndef NIXIE_DIRECTX_H_
#define NIXIE_DIRECTX_H_

#pragma once

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")

#include <d3d11.h>

#include "SimpleMath.h"
#include "WICTextureLoader.h"

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
		static D3D* singleton_;

		bool vsync_enabled_;
		bool fullscreen_enabled_;
		bool msaa_enabled_;
		bool wireframe_mode_enabled_;

		ID3D11Device* device_;
		ID3D11DeviceContext* device_context_;
		IDXGISwapChain* swap_chain_;
		D3D_FEATURE_LEVEL feature_level_;

		UINT adapter_memory_;
		char adapter_desc_[128];

		ID3D11RenderTargetView* render_target_view_;
		ID3D11Texture2D* depth_stencil_buffer_;
		ID3D11DepthStencilState* depth_stencil_state_;
		ID3D11DepthStencilView* depth_stencil_view_;
		ID3D11RasterizerState* rasterizer_state_;

		DirectX::SimpleMath::Matrix projection_matrix_;
		DirectX::SimpleMath::Matrix ortho_matrix_;
	};
}

#endif