#include "Graphics.h"
#include "..\Engine.h"

Graphics::Graphics()
{
	camera_ = nullptr;
}

Graphics* Graphics::singleton_;

Graphics* Graphics::GetSingleton()
{
	if (singleton_ == 0)
		singleton_ = new Graphics;

	return singleton_;
}

void Graphics::Release()
{
	safe_delete(color_shader_);
	safe_delete(camera_);
	safe_release(D3D::GetSingleton());
}

bool Graphics::Init(UINT screen_width, UINT screen_height, bool vsync_enabled, bool fullscreen_enabled)
{
	if (!D3D::GetSingleton()->Init(screen_width, screen_height, vsync_enabled, fullscreen_enabled, 1000.0f, 0.1f))
	{
		MessageBox(Engine::GetSingleton()->GetHwnd(), "DirectX initialization failed", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	camera_ = new Camera;
	if (!camera_)
		return false;

	color_shader_ = new ColorShader;
	if (!color_shader_)
		return false;

	if (!color_shader_->Init())
	{
		MessageBox(Engine::GetSingleton()->GetHwnd(), "Could not initialize the color shader object.", "Error", MB_OK);
		return false;
	}

	camera_->position_ = new Vector3(0.0f, 0.0f, -10.0f);

	return true;
}

void Graphics::Render()
{
	D3D::GetSingleton()->BeginScene(Engine::GetSingleton()->GetCurrentScene()->GetClearColor());

	XMMATRIX world_matrix;
	XMMATRIX view_matrix;
	XMMATRIX projection_matrix;

	camera_->Render();
	D3D::GetSingleton()->GetWorldMatrix(world_matrix);
	camera_->GetViewMatrix(view_matrix);
	D3D::GetSingleton()->GetProjectionMatrix(projection_matrix);

	Engine::GetSingleton()->GetCurrentScene()->Update();

	D3D::GetSingleton()->EndScene();
}