#include "Graphics.h"
#include "..\Engine.h"

CGraphics::CGraphics()
{
	m_pCamera = 0;
}

CGraphics* CGraphics::s_singleton;

CGraphics* CGraphics::GetSingleton()
{
	if (s_singleton == 0)
		s_singleton = new CGraphics;

	return s_singleton;
}

void CGraphics::Release()
{
	safe_delete(m_pColorShader);
	safe_delete(m_pCamera);
	safe_release(CDirectX::GetSingleton());
}

bool CGraphics::Init(UINT screenWidth, UINT screenHeight, bool vsyncEnabled, bool fullscreenEnabled)
{
	m_vsyncEnabled = vsyncEnabled;
	m_fullscreenEnabled = fullscreenEnabled;

	if (!CDirectX::GetSingleton()->Init(screenWidth, screenHeight, vsyncEnabled, fullscreenEnabled, 1000.0f, 0.1f))
	{
		MessageBox(CEngine::GetSingleton()->GetHwnd(), "DirectX initialization failed", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	m_pCamera = new CCamera;
	if (!m_pCamera)
		return false;

	m_pColorShader = new CColorShader;
	if (!m_pColorShader)
		return false;

	if (!m_pColorShader->Init())
	{
		MessageBox(CEngine::GetSingleton()->GetHwnd(), "Could not initialize the color shader object.", "Error", MB_OK);
		return false;
	}

	m_pCamera->SetPosition(0.0f, 0.0f, -5.0f);

	return true;
}

void CGraphics::Render()
{
	CDirectX::GetSingleton()->BeginScene(CEngine::GetSingleton()->GetCurrentScene()->GetClearColor());

	m_pCamera->Render();

	XMMATRIX worldMatrix;
	CDirectX::GetSingleton()->GetWorldMatrix(worldMatrix);
	XMMATRIX viewMatrix;
	m_pCamera->GetViewMatrix(viewMatrix);
	XMMATRIX projectionMatrix;
	CDirectX::GetSingleton()->GetProjectionMatrix(projectionMatrix);

	CEngine::GetSingleton()->GetCurrentScene()->Update();

	CDirectX::GetSingleton()->EndScene();
}