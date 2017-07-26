#include "DirectX.h"

namespace NixieClient
{
	DirectX::DirectX()
	{
		m_pDevice = nullptr;
		m_pImmediateContext = nullptr;
		m_pSwapChain = nullptr;
		m_pRenderTargetView = nullptr;
	}

	DirectX::~DirectX()
	{
		if (m_pImmediateContext)
			m_pImmediateContext->ClearState();

		SafeRelease(m_pRenderTargetView);
		SafeRelease(m_pSwapChain);
		SafeRelease(m_pImmediateContext);
		SafeRelease(m_pDevice);
	}

	bool DirectX::Init(HWND hwnd, int clientWidth, int clientHeight, bool vsync, bool fullscreen, float depth, float nearClip)
	{
		HRESULT result;

		UINT createDeviceFlags = 0;

#ifdef DEBUG
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // DEBUG

		D3D_DRIVER_TYPE driverTypes[] =
		{
			D3D_DRIVER_TYPE_HARDWARE,
			D3D_DRIVER_TYPE_WARP,
			D3D_DRIVER_TYPE_REFERENCE,
		};

		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
		};

		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferDesc.Width = clientWidth;
		swapChainDesc.BufferDesc.Height = clientHeight;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = hwnd;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Windowed = !fullscreen;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		for (UINT i = 0; i < ARRAYSIZE(driverTypes); i++)
		{
			result = D3D11CreateDeviceAndSwapChain(NULL,
				driverTypes[i],
				NULL,
				createDeviceFlags,
				featureLevels,
				ARRAYSIZE(featureLevels),
				D3D11_SDK_VERSION,
				&swapChainDesc,
				&m_pSwapChain,
				&m_pDevice,
				&m_FeatureLevel,
				&m_pImmediateContext);
			if (SUCCEEDED(result))
			{
				m_DriverType = driverTypes[i];
				break;
			}
		}
		if (FAILED(result))
		{
			MessageBox(hwnd, "Failed to create device and swap chain", "DirectX Error", MB_OK);
			return false;
		}

		ID3D11Texture2D* pBackBufferTexture = 0;
		result = m_pSwapChain->GetBuffer(NULL, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBufferTexture));
		if (FAILED(result))
		{
			MessageBox(hwnd, "Failed to create back buffer texture", "DirectX Error", MB_OK);
			return false;
		}
		result = m_pDevice->CreateRenderTargetView(pBackBufferTexture, nullptr, &m_pRenderTargetView);
		if (FAILED(result))
		{
			MessageBox(hwnd, "Failed to create render target view", "DirectX Error", MB_OK);
			return false;
		}
		SafeRelease(pBackBufferTexture);

		m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, nullptr);

		m_Viewport.Width = static_cast<float>(clientWidth);
		m_Viewport.Height = static_cast<float>(clientHeight);
		m_Viewport.TopLeftX = 0;
		m_Viewport.TopLeftY = 0;
		m_Viewport.MinDepth = 0.0f;
		m_Viewport.MaxDepth = 1.0f;

		m_pImmediateContext->RSSetViewports(1, &m_Viewport);

		return true;
	}

	void DirectX::Render()
	{
		m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, Colors::SlateGray);
		m_pSwapChain->Present(0, 0);
	}
}