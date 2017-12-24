#include "Graphics.h"
#include "..\Engine.h"

Graphics::Graphics()
{
	m_pCamera = 0;
}

Graphics* Graphics::s_singleton;

Graphics* Graphics::GetSingleton()
{
	if (s_singleton == 0)
		s_singleton = new Graphics;

	return s_singleton;
}

void Graphics::Release()
{
	safe_delete(m_pColorShader);
	safe_delete(m_pCamera);
	safe_release(D3D::GetSingleton());
}

bool Graphics::Init(UINT screenWidth, UINT screenHeight, bool vsyncEnabled, bool fullscreenEnabled)
{
	m_vsyncEnabled = vsyncEnabled;
	m_fullscreenEnabled = fullscreenEnabled;

	if (!D3D::GetSingleton()->Init(screenWidth, screenHeight, vsyncEnabled, fullscreenEnabled, 1000.0f, 0.1f))
	{
		MessageBox(Engine::GetSingleton()->GetHwnd(), "DirectX initialization failed", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	m_pCamera = new Camera;
	if (!m_pCamera)
		return false;

	m_pColorShader = new ColorShader;
	if (!m_pColorShader)
		return false;

	if (!m_pColorShader->Init())
	{
		MessageBox(Engine::GetSingleton()->GetHwnd(), "Could not initialize the color shader object.", "Error", MB_OK);
		return false;
	}

	m_pCamera->position_ = new Vector3(0.0f, 0.0f, -10.0f);

	return true;
}

void Graphics::Render()
{
	D3D::GetSingleton()->BeginScene(Engine::GetSingleton()->GetCurrentScene()->GetClearColor());

	m_pCamera->Render();

	XMMATRIX worldMatrix;
	D3D::GetSingleton()->GetWorldMatrix(worldMatrix);
	XMMATRIX viewMatrix;
	m_pCamera->GetViewMatrix(viewMatrix);
	XMMATRIX projectionMatrix;
	D3D::GetSingleton()->GetProjectionMatrix(projectionMatrix);

	Engine::GetSingleton()->GetCurrentScene()->Update();

	D3D::GetSingleton()->EndScene();
}