#include "../../stdafx.h"

#include "d3d.h"
#include "../app.h"

namespace Nixie
{
	D3D::D3D() :
		swap_chain(nullptr),
		device(nullptr),
		device_context(nullptr),
		render_target_view(nullptr),
		depth_stencil_buffer(nullptr),
		depth_stencil_state(nullptr),
		depth_stencil_view(nullptr),
		rasterizer_state(nullptr) {}

	D3D* D3D::singleton;

	D3D* D3D::GetSingleton()
	{
		if (singleton == 0)
			singleton = new D3D;

		return singleton;
	}

	bool D3D::Init(
		unsigned int screen_width,
		unsigned int screen_height,
		bool vsync_enabled,
		bool fullscreen_enabled,
		float screen_depth,
		float screen_near)
	{
		HRESULT hr = S_OK;

		this->vsync_enabled = vsync_enabled;
		this->fullscreen_enabled = fullscreen_enabled;
		this->msaa_enabled = false;
		this->wireframe_mode_enabled = false;

		IDXGIFactory* factory;
		hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
		if (FAILED(hr))
		{
			std::cerr << "Failed to create DXGIFactory" << std::endl;
			return false;
		}

		IDXGIAdapter* adapter;
		hr = factory->EnumAdapters(0, &adapter);
		if (FAILED(hr))
		{
			std::cerr << "Failed to enum adapters" << std::endl;
			return false;
		}

		IDXGIOutput* adapter_output;
		hr = adapter->EnumOutputs(0, &adapter_output);
		if (FAILED(hr))
		{
			std::cerr << "Failed to enum adapter outputs" << std::endl;
			return false;
		}

		UINT num_modes;
		hr = adapter_output->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &num_modes, NULL);
		if (FAILED(hr))
		{
			std::cerr << "Failed to get the number of modes" << std::endl;
			return false;
		}

		DXGI_MODE_DESC* display_mode_list;
		display_mode_list = new DXGI_MODE_DESC[num_modes];
		if (!display_mode_list)
		{
			std::cerr << "Failed to create mode list" << std::endl;
			return false;
		}

		hr = adapter_output->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &num_modes, display_mode_list);
		if (FAILED(hr))
		{
			std::cerr << "Failed to fill display mode list struct" << std::endl;
			return false;
		}

		UINT numerator, denominator;
		for (UINT i = 0; i < num_modes; i++)
		{
			if (display_mode_list[i].Width == static_cast<UINT>(screen_width))
			{
				if (display_mode_list[i].Height == static_cast<UINT>(screen_height))
				{
					numerator = display_mode_list[i].RefreshRate.Numerator;
					denominator = display_mode_list[i].RefreshRate.Denominator;
				}
			}
		}

		DXGI_ADAPTER_DESC adapter_desc;
		hr = adapter->GetDesc(&adapter_desc);
		if (FAILED(hr))
		{
			std::cerr << "Failed to get adapter description" << std::endl;
			return false;
		}

		adapter_memory = (UINT)(adapter_desc.DedicatedVideoMemory / 1024 / 1024);

		//size_t stringLength;
		//int error = wcstombs_s(&stringLength, adapter_desc_, 128, adapter_desc.Description, 128);
		//if (error != 0)
		//{
		//	std::cerr << "Failed to convert the name of the video card. Error:" << error << std::endl;
		//	return false;
		//}

		UINT device_creation_flags = 0;
#if defined(_DEBUG)
		device_creation_flags = D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D_DRIVER_TYPE driver_types[] = {
			D3D_DRIVER_TYPE_HARDWARE,
			D3D_DRIVER_TYPE_SOFTWARE,
			D3D_DRIVER_TYPE_WARP,
		};

		D3D_FEATURE_LEVEL feature_levels[] = {
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1
		};

		for (int i = 0; i < ARRAYSIZE(driver_types); i++)
		{
			D3D_DRIVER_TYPE driver_type = driver_types[i];

			for (int y = 0; y < ARRAYSIZE(feature_levels); y++)
			{
				hr = D3D11CreateDevice(
					0,
					driver_type,
					0,
					device_creation_flags,
					&feature_levels[y], ARRAYSIZE(feature_levels),
					D3D11_SDK_VERSION,
					&device,
					&feature_level,
					&device_context);

				if (SUCCEEDED(hr))
					break;
			}

			if (SUCCEEDED(hr))
				break;
		}
		if (FAILED(hr))
		{
			std::cerr << "Failed to create DirectX device" << std::endl;
			return false;
		}

		UINT msaa_quality;
		hr = device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &msaa_quality);
		if (FAILED(hr))
		{
			std::cerr << "Failed to check multisample quality levels" << std::endl;
			return false;
		}

		DXGI_SWAP_CHAIN_DESC swap_chain_desc;
		ZeroMemory(&swap_chain_desc, sizeof(swap_chain_desc));
		swap_chain_desc.OutputWindow = App::GetSingleton()->GetHwnd();
		swap_chain_desc.Windowed = !this->fullscreen_enabled;
		swap_chain_desc.BufferDesc.Width = screen_width;
		swap_chain_desc.BufferDesc.Height = screen_height;
		swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swap_chain_desc.BufferDesc.RefreshRate.Numerator = this->vsync_enabled ? numerator : 0;
		swap_chain_desc.BufferDesc.RefreshRate.Denominator = this->vsync_enabled ? denominator : 1;
		swap_chain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swap_chain_desc.BufferCount = 1;
		swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swap_chain_desc.Flags = 0;
		swap_chain_desc.SampleDesc.Count = this->msaa_enabled ? 4 : 1;
		swap_chain_desc.SampleDesc.Quality = this->msaa_enabled ? msaa_quality - 1 : 0;

		hr = factory->CreateSwapChain(device, &swap_chain_desc, &swap_chain);
		if (FAILED(hr))
		{
			std::cerr << "Failed to create swap chain" << std::endl;
			return false;
		}

		safe_delete_arr(display_mode_list);
		safe_release(adapter_output);
		safe_release(adapter);
		safe_release(factory);

		ID3D11Texture2D* back_buffer;
		hr = swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buffer);
		if (FAILED(hr))
		{
			std::cerr << "Failed to get the back buffer" << std::endl;
			return false;
		}

		//D3D11_TEXTURE2D_DESC render_target_texture_desc;
		//ZeroMemory(&render_target_texture_desc, sizeof(render_target_texture_desc));
		//render_target_texture_desc.Width = screen_width;
		//render_target_texture_desc.Height = screen_height;
		//render_target_texture_desc.MipLevels = 1;
		//render_target_texture_desc.ArraySize = 1;
		//render_target_texture_desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		//render_target_texture_desc.Usage = D3D11_USAGE_DEFAULT;
		//render_target_texture_desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		//render_target_texture_desc.CPUAccessFlags = 0;
		//render_target_texture_desc.MiscFlags = 0;
		//render_target_texture_desc.SampleDesc.Count = msaa_enabled_ ? 4 : 1;
		//render_target_texture_desc.SampleDesc.Quality = msaa_enabled_ ? msaa_quality - 1 : 0;

		//D3D11_RENDER_TARGET_VIEW_DESC render_target_view_desc;
		//render_target_view_desc.Format = render_target_texture_desc.Format;
		//render_target_view_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		//render_target_view_desc.Texture2D.MipSlice = 0;

		//ID3D11Texture2D* render_target_texture;
		//hr = device_->CreateTexture2D(&render_target_texture_desc, NULL, &render_target_texture);
		//if (FAILED(hr))
		//{
		//	std::cerr << "Failed to create back buffer texture" << std::endl;
		//	return false;
		//}

		hr = device->CreateRenderTargetView(back_buffer, NULL, &render_target_view);
		if (FAILED(hr))
		{
			std::cerr << "Failed to create render target view" << std::endl;
			return false;
		}

		safe_release(back_buffer);

		D3D11_TEXTURE2D_DESC depth_buffer_desc;
		ZeroMemory(&depth_buffer_desc, sizeof(depth_buffer_desc));
		depth_buffer_desc.Width = screen_width;
		depth_buffer_desc.Height = screen_height;
		depth_buffer_desc.MipLevels = 1;
		depth_buffer_desc.ArraySize = 1;
		depth_buffer_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depth_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
		depth_buffer_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depth_buffer_desc.CPUAccessFlags = 0;
		depth_buffer_desc.MiscFlags = 0;
		depth_buffer_desc.SampleDesc.Count = this->msaa_enabled ? 4 : 1;
		depth_buffer_desc.SampleDesc.Quality = this->msaa_enabled ? msaa_quality - 1 : 0;

		hr = device->CreateTexture2D(&depth_buffer_desc, NULL, &depth_stencil_buffer);
		if (FAILED(hr))
		{
			std::cerr << "Failed to create back buffer texture" << std::endl;
			return false;
		}

		D3D11_DEPTH_STENCIL_DESC depth_stencil_desc;
		ZeroMemory(&depth_stencil_desc, sizeof(depth_stencil_desc));
		depth_stencil_desc.DepthEnable = true;
		depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depth_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS;
		depth_stencil_desc.StencilEnable = true;
		depth_stencil_desc.StencilReadMask = 0xFF;
		depth_stencil_desc.StencilWriteMask = 0xFF;
		depth_stencil_desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depth_stencil_desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		depth_stencil_desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depth_stencil_desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		depth_stencil_desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depth_stencil_desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		depth_stencil_desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depth_stencil_desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		hr = device->CreateDepthStencilState(&depth_stencil_desc, &depth_stencil_state);
		if (FAILED(hr))
		{
			std::cerr << "Failed to create depth stencil state" << std::endl;
			return false;
		}

		device_context->OMSetDepthStencilState(depth_stencil_state, 1);

		D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc;
		ZeroMemory(&depth_stencil_view_desc, sizeof(depth_stencil_view_desc));
		depth_stencil_view_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depth_stencil_view_desc.Texture2D.MipSlice = 0;

		hr = device->CreateDepthStencilView(depth_stencil_buffer, &depth_stencil_view_desc, &depth_stencil_view);
		if (FAILED(hr))
		{
			std::cerr << "Failed to create depth stencil view" << hr << std::endl;
			return false;
		}

		device_context->OMSetRenderTargets(1, &render_target_view, depth_stencil_view);

		if (!SetRasterizer())
		{
			std::cerr << "Failed to create rasterizer state" << std::endl;
			return false;
		}

		D3D11_VIEWPORT viewport;
		ZeroMemory(&viewport, sizeof(viewport));
		viewport.Width = static_cast<float>(screen_width);
		viewport.Height = static_cast<float>(screen_height);
		viewport.MinDepth = 0;
		viewport.MaxDepth = 1;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;

		device_context->RSSetViewports(1, &viewport);

		float fov = DirectX::XM_PIDIV4;
		float aspect_ratio = static_cast<float>(screen_width) / static_cast<float>(screen_height);

		projection_matrix = DirectX::XMMatrixPerspectiveFovLH(fov, aspect_ratio, screen_near, screen_depth);
		ortho_matrix = DirectX::XMMatrixOrthographicLH(static_cast<float>(screen_width), static_cast<float>(screen_height), screen_near, screen_depth);

		return true;
	}

	bool D3D::SetRasterizer()
	{
		HRESULT hr;

		D3D11_RASTERIZER_DESC rasterizer_desc;
		rasterizer_desc.AntialiasedLineEnable = false;
		rasterizer_desc.CullMode = D3D11_CULL_BACK;
		rasterizer_desc.DepthBias = 0;
		rasterizer_desc.DepthBiasClamp = 0.0f;
		rasterizer_desc.DepthClipEnable = true;
		rasterizer_desc.FrontCounterClockwise = false;
		rasterizer_desc.MultisampleEnable = false;
		rasterizer_desc.ScissorEnable = false;
		rasterizer_desc.SlopeScaledDepthBias = 0.0f;
		rasterizer_desc.FillMode = wireframe_mode_enabled ? D3D11_FILL_WIREFRAME : D3D11_FILL_SOLID;

		hr = device->CreateRasterizerState(&rasterizer_desc, &rasterizer_state);
		if (FAILED(hr))
			return false;

		device_context->RSSetState(rasterizer_state);

		return true;
	}

	void D3D::ToggleWireframeMode()
	{
		wireframe_mode_enabled = !wireframe_mode_enabled;
		SetRasterizer();
	}

	void D3D::Release()
	{
		if (swap_chain)
			swap_chain->SetFullscreenState(false, NULL);

		if (rasterizer_state)
			safe_release(rasterizer_state);

		if (depth_stencil_view)
			safe_release(depth_stencil_view);

		if (depth_stencil_state)
			safe_release(depth_stencil_state);

		if (depth_stencil_buffer)
			safe_release(depth_stencil_buffer);

		if (render_target_view)
			safe_release(render_target_view);

		if (device_context)
			safe_release(device_context);

		if (device)
			safe_release(device);

		if (swap_chain)
			safe_release(swap_chain);
	}

	void D3D::BeginScene(Color clear_color)
	{
#ifdef _DEBUG
		if (Input::IsKeyPressed(DirectX::Keyboard::Keys::F1))
			ToggleWireframeMode();
#endif
		auto dx_clear_color = DirectX::SimpleMath::Color(clear_color.r, clear_color.g, clear_color.b);

		device_context->ClearRenderTargetView(render_target_view, dx_clear_color);
		device_context->ClearDepthStencilView(depth_stencil_view, D3D11_CLEAR_DEPTH, 1.0f, 0);
	}

	void D3D::EndScene()
	{
		if (vsync_enabled)
		{
			swap_chain->Present(1, 0);
		}
		else
		{
			swap_chain->Present(0, 0);
		}
	}

	ID3D11Device* D3D::GetDevice()
	{
		return device;
	}

	ID3D11DeviceContext* D3D::GetDeviceContext()
	{
		return device_context;
	}

	DirectX::SimpleMath::Matrix D3D::GetProjectionMatrix()
	{
		return projection_matrix;
	}

	DirectX::SimpleMath::Matrix D3D::GetOrthoMatrix()
	{
		return ortho_matrix;
	}
}