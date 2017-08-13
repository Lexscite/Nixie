#include "Graphics.h"

CGraphics::CGraphics() {}

CGraphics* CGraphics::s_singleton;

CGraphics* CGraphics::GetSingleton()
{
	if (s_singleton == 0)
		s_singleton = new CGraphics;

	return s_singleton;
}

void CGraphics::Release()
{
	safe_release(CDirectX::GetSingleton());
}

bool CGraphics::Init(HWND hwnd, int clientWidth, int clientHeight, bool fullscreen)
{
	m_Fullscreen = fullscreen;

	std::cout << "DirectX iniitialization..." << std::endl;
	if (!CDirectX::GetSingleton()->Init())
	{
		std::cerr << "Failed to initialize DirectX" << std::endl;
		MessageBox(hwnd, "DirectX initialization failed", "Error", MB_OK | MB_ICONERROR);
		return false;
	}
	std::cout << "OK" << std::endl;

	return true;
}

void CGraphics::Render()
{
}