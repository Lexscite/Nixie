#ifndef NIXIE_DIRECTX_MANAGER_H_
#define NIXIE_DIRECTX_MANAGER_H_

#pragma once

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")

#include <d3d11.h>

#include "WICTextureLoader.h"
#include "math/color.h"


namespace nixie
{
	class Color;

	class DirectXManager final
	{
	public:
		static DirectXManager* Get();

		bool Init(
			HWND window,
			unsigned int screen_width,
			unsigned int screen_height,
			bool vsync_enabled,
			bool fullscreen_enabled);
		void Release();

		void BeginScene(const Color& c);
		void EndScene();

		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetDeviceContext();

		void ToggleWireframeMode();
		void ToggleBlendMode();

	private:
		DirectXManager();

		bool CreateRasterizerStates();
		bool CreateBlendStates();

	private:
		static DirectXManager* singleton_;

		bool vsync_enabled_;
		bool fullscreen_enabled_;
		bool msaa_enabled_;
		bool wireframe_mode_enabled_;
		bool alpha_blending_enabled_;

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
		ID3D11RasterizerState* rasterizer_state_wireframe_mode_on_;
		ID3D11RasterizerState* rasterizer_state_wireframe_mode_off_;
		ID3D11BlendState* blend_state_on_;
		ID3D11BlendState* blend_state_off_;
	};
}

#endif