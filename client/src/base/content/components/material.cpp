#include "material.h"
#include "../../app.h"

Material::Material()
{
	shader_ = nullptr;
	texture_ = nullptr;
}

void Material::OnInit()
{
	LoadTexture(L"../data/textures/placeholder.jpg");

	shader_ = new Shader;
	shader_->Init(L"../data/shaders/default.hlsl.");
}

void Material::OnUpdate()
{
	Vector3 position = GetPosition();
	Vector3 rotation = GetRotation();
	Vector3 scale = GetScale();

	XMMATRIX translation_matrix = XMMatrixTranslation(position.x, position.y, position.z);
	XMMATRIX rotation_matrix = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
	XMMATRIX scaling_matrix = XMMatrixScaling(scale.x, scale.y, scale.z);

	shader_->Update(
		translation_matrix * rotation_matrix * scaling_matrix,
		App::GetSingleton()->GetScene()->GetCamera()->GetViewMatrix(),
		D3D::GetSingleton()->GetProjectionMatrix(),
		texture_->GetTextureView());
}

bool Material::LoadTexture(const wchar_t* file_path)
{
	texture_ = new Texture;
	if (!texture_->Init(file_path))
		return false;

	return true;
}

Shader* Material::GetShader()
{
	return shader_;
}