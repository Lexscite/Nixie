#include "Graphics.h"
#include "..\Engine.h"

Graphics::Graphics() = default;

Graphics* Graphics::singleton_;

Graphics* Graphics::GetSingleton()
{
	if (singleton_ == 0)
		singleton_ = new Graphics;

	return singleton_;
}

void Graphics::Release()
{
	safe_release(D3D::GetSingleton());
}

bool Graphics::Init(UINT screen_width, UINT screen_height, bool vsync_enabled, bool fullscreen_enabled)
{
	if (!D3D::GetSingleton()->Init(screen_width, screen_height, vsync_enabled, fullscreen_enabled, 1000.0f, 0.1f))
	{
		MessageBox(Engine::GetSingleton()->GetHwnd(), "DirectX initialization failed", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	return true;
}

bool Graphics::Render()
{
	XMMATRIX world_matrix;
	XMMATRIX view_matrix;
	XMMATRIX projection_matrix;

	D3D::GetSingleton()->BeginScene(Engine::GetSingleton()->GetCurrentScene()->GetClearColor());


	Scene* scene = Engine::GetSingleton()->GetCurrentScene();
	Camera* camera = scene->GetCamera();
	std::vector<GameObject*> game_objects = scene->GetGameObjects();

	camera->Render();
	camera->GetViewMatrix(view_matrix);
	D3D::GetSingleton()->GetWorldMatrix(world_matrix);
	D3D::GetSingleton()->GetProjectionMatrix(projection_matrix);

	for (int i = 0; i < game_objects.size(); i++)
	{
		Mesh* mesh = game_objects[i]->GetMesh();
		mesh->Render();
		ColorShader* shader = game_objects[i]->GetShader();
		shader->Render(mesh->GetIndexCount(), world_matrix, view_matrix, projection_matrix);
	}

	D3D::GetSingleton()->EndScene();

	return true;
}