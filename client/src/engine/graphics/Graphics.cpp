#include "Graphics.h"
#include "..\Engine.h"

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

bool CGraphics::Init(UINT screenWidth, UINT screenHeight, bool vsyncEnabled, bool fullscreenEnabled)
{
	m_vsyncEnabled = vsyncEnabled;
	m_fullscreenEnabled = fullscreenEnabled;

	if (!CDirectX::GetSingleton()->Init(screenWidth, screenHeight, vsyncEnabled, fullscreenEnabled))
	{
		MessageBox(CEngine::GetSingleton()->GetHwnd(), "DirectX initialization failed", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	return true;
}

void CGraphics::Render()
{

}