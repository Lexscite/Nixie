#include "DirectX.h"
#include "..\Engine.h"

CDirectX::CDirectX()
{
}

CDirectX* CDirectX::s_singleton;

CDirectX* CDirectX::GetSingleton()
{
	if (s_singleton == 0)
		s_singleton = new CDirectX;

	return s_singleton;
}

bool CDirectX::Init(UINT screenWidth, UINT screenHeight, bool vsyncEnabled, bool fullscreenEnabled)
{
	HRESULT result = S_OK;

	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
	m_vsyncEnabled = vsyncEnabled;
	m_fullscreenEnabled = fullscreenEnabled;

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = screenWidth;
	swapChainDesc.BufferDesc.Height = screenHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = CEngine::GetSingleton()->GetHwnd();
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = !fullscreenEnabled;

	D3D_FEATURE_LEVEL FeatureLevels[] = {
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	for (int i = 0; i < ARRAYSIZE(FeatureLevels); i++)
	{
		if (SUCCEEDED(result = D3D11CreateDeviceAndSwapChain(NULL,
			D3D_DRIVER_TYPE_REFERENCE,
			NULL,
			0,
			&FeatureLevels[i],
			6,
			D3D11_SDK_VERSION,
			&swapChainDesc,
			&m_pSwapChain,
			&m_pDevice,
			&m_featureLevel,
			&m_pDeviceContext)))
		{
			break;
		}
	}
	if (FAILED(result))
	{
		std::cerr << "Failed to create DirectX device and swap chain" << std::endl;
		return false;
	}

	return true;
}

void CDirectX::Release()
{

}