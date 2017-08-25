#include "DirectX.h"
#include "..\Engine.h"

CDirectX::CDirectX()
{
	m_pSwapChain = 0;
	m_pDevice = 0;
	m_pDeviceContext = 0;
	m_pRenderTargetView = 0;
	m_pDepthStencilBuffer = 0;
	m_pDepthStencilState = 0;
	m_pDepthStencilView = 0;
	m_pRasterizerState = 0;
}

CDirectX* CDirectX::s_singleton;

CDirectX* CDirectX::GetSingleton()
{
	if (s_singleton == 0)
		s_singleton = new CDirectX;

	return s_singleton;
}

bool CDirectX::Init(UINT screenWidth, UINT screenHeight, bool vsyncEnabled, bool fullscreenEnabled, float screenDepth, float screenNear)
{
	HRESULT result = S_OK;

	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
	m_vsyncEnabled = vsyncEnabled;
	m_fullscreenEnabled = fullscreenEnabled;

	IDXGIFactory* pFactory;
	result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory);
	if (FAILED(result))
	{
		std::cerr << "Failed to create DXGIFactory" << std::endl;
		return false;
	}

	IDXGIAdapter* pAdapter;
	result = pFactory->EnumAdapters(0, &pAdapter);
	if (FAILED(result))
	{
		std::cerr << "Failed to enum adapters" << std::endl;
		return false;
	}

	IDXGIOutput* pAdapterOutput;
	result = pAdapter->EnumOutputs(0, &pAdapterOutput);
	if (FAILED(result))
	{
		std::cerr << "Failed to enum adapter outputs" << std::endl;
		return false;
	}

	UINT numModes;
	result = pAdapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	if (FAILED(result))
	{
		std::cerr << "Failed to get the number of modes" << std::endl;
		return false;
	}

	DXGI_MODE_DESC* pDisplayModeList;
	pDisplayModeList = new DXGI_MODE_DESC[numModes];
	if (!pDisplayModeList)
	{
		std::cerr << "Failed to create mode list" << std::endl;
		return false;
	}

	result = pAdapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, pDisplayModeList);
	if (FAILED(result))
	{
		std::cerr << "Failed to fill display mode list struct" << std::endl;
		return false;
	}

	UINT numerator, denominator;
	for (UINT i = 0; i<numModes; i++)
	{
		if (pDisplayModeList[i].Width == (unsigned int)screenWidth)
		{
			if (pDisplayModeList[i].Height == (unsigned int)screenHeight)
			{
				numerator = pDisplayModeList[i].RefreshRate.Numerator;
				denominator = pDisplayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	DXGI_ADAPTER_DESC adapterDesc;
	result = pAdapter->GetDesc(&adapterDesc);
	if (FAILED(result))
	{
		std::cerr << "Failed to get adapter desc" << std::endl;
		return false;
	}

	m_adapterMemory = (UINT)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

	size_t stringLength;
	int error = wcstombs_s(&stringLength, m_pAdapterDesc, 128, adapterDesc.Description, 128);
	if (error != 0)
	{
		return false;
	}

	safe_delete_arr(pDisplayModeList);
	safe_release(pAdapterOutput);
	safe_release(pAdapter);
	safe_release(pFactory);

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.OutputWindow = CEngine::GetSingleton()->GetHwnd();
	swapChainDesc.Windowed = !m_fullscreenEnabled;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = screenWidth;
	swapChainDesc.BufferDesc.Height = screenHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = m_vsyncEnabled ? numerator : 0;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = m_vsyncEnabled ? denominator : 1;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;

	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	for (int i = 0; i < ARRAYSIZE(featureLevels); i++)
	{
		result = D3D11CreateDeviceAndSwapChain(
			NULL,
			D3D_DRIVER_TYPE_REFERENCE,
			NULL,
			0,
			&featureLevels[i],
			6,
			D3D11_SDK_VERSION,
			&swapChainDesc,
			&m_pSwapChain,
			&m_pDevice,
			&m_featureLevel,
			&m_pDeviceContext
		);

		if (SUCCEEDED(result))
			break;
	}
	if (FAILED(result))
	{
		std::cerr << "Failed to create DirectX device and swap chain" << std::endl;
		return false;
	}

	ID3D11Texture2D* pBackBuffer;
	result = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(result))
	{
		std::cerr << "Failed to get the back buffer pointer" << std::endl;
		return false;
	}

	result = m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
	if (FAILED(result))
	{
		std::cerr << "Failed to create render target view" << std::endl;
		return false;
	}

	safe_release(pBackBuffer);

	D3D11_TEXTURE2D_DESC depthBufferDesc;
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));
	depthBufferDesc.Width = screenWidth;
	depthBufferDesc.Height = screenHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	result = m_pDevice->CreateTexture2D(&depthBufferDesc, NULL, &m_pDepthStencilBuffer);
	if (FAILED(result))
	{
		std::cerr << "Failed to create back buffer texture" << std::endl;
		return false;
	}

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	
	result = m_pDevice->CreateDepthStencilState(&depthStencilDesc, &m_pDepthStencilState);
	if (FAILED(result))
	{
		std::cerr << "Failed to create depth stencil state" << std::endl;
		return false;
	}

	m_pDeviceContext->OMSetDepthStencilState(m_pDepthStencilState, 1);

	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	result = m_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer, &depthStencilViewDesc, &m_pDepthStencilView);
	if (FAILED(result))
	{
		std::cerr << "Failed to create depth stencil view" << result << std::endl;
		return false;
	}

	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

	D3D11_RASTERIZER_DESC rasterizerDesc;
	rasterizerDesc.AntialiasedLineEnable = false;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	rasterizerDesc.DepthBias = 0;
	rasterizerDesc.DepthBiasClamp = 0.0f;
	rasterizerDesc.DepthClipEnable = true;
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.FrontCounterClockwise = false;
	rasterizerDesc.MultisampleEnable = false;
	rasterizerDesc.ScissorEnable = false;
	rasterizerDesc.SlopeScaledDepthBias = 0.0f;

	result = m_pDevice->CreateRasterizerState(&rasterizerDesc, &m_pRasterizerState);
	if (FAILED(result))
	{
		std::cerr << "Failed to create rasterizer state" << std::endl;
		return false;
	}

	m_pDeviceContext->RSSetState(m_pRasterizerState);

	D3D11_VIEWPORT viewport;
	viewport.Width = (FLOAT)screenWidth;
	viewport.Height = (FLOAT)screenHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	m_pDeviceContext->RSSetViewports(1, &viewport);

	float fieldOfView = 3.141592654f / 4.0f;
	float screenAspect = (float)(screenWidth / screenHeight);
	m_projectionMatrix = XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, screenNear, screenDepth);
	m_worldMatrix = XMMatrixIdentity();
	m_orthoMatrix = XMMatrixOrthographicLH((float)screenWidth, (float)screenHeight, screenNear, screenDepth);

	return true;
}

void CDirectX::Release()
{
	if (m_pSwapChain)
		m_pSwapChain->SetFullscreenState(false, NULL);

	if (m_pRasterizerState)
		safe_release(m_pRasterizerState);

	if (m_pDepthStencilView)
		safe_release(m_pDepthStencilView);

	if (m_pDepthStencilState)
		safe_release(m_pDepthStencilState);

	if (m_pDepthStencilBuffer)
		safe_release(m_pDepthStencilBuffer);

	if (m_pRenderTargetView)
		safe_release(m_pRenderTargetView);

	if (m_pDeviceContext)
		safe_release(m_pDeviceContext);

	if (m_pDevice)
		safe_release(m_pDevice);

	if (m_pSwapChain)
		safe_release(m_pSwapChain);
}

void CDirectX::BeginScene(Color* color)
{
	float clearColor[4] = { color->r, color->g, color->b, color->a };
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, clearColor);
	m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void CDirectX::EndScene()
{
	if (m_vsyncEnabled)
		m_pSwapChain->Present(1, 0);
	else
		m_pSwapChain->Present(0, 0);
}