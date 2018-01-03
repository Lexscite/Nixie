#include "material.h"
#include "../../app.h"

Material::Material()
{
	shader_ = nullptr;
}

void Material::OnInit()
{
	shader_ = new Shader;
	shader_->Init();
}

void Material::OnUpdate()
{
	Vector3* position = GetGameObject()->GetPosition();
	Vector3* rotation = GetGameObject()->GetRotation();
	Vector3* scale = GetGameObject()->GetScale();

	XMMATRIX translation_matrix = XMMatrixTranslation(position->x, position->y, position->z);
	XMMATRIX rotation_matrix = XMMatrixRotationRollPitchYaw(rotation->x, rotation->y, rotation->z);
	XMMATRIX scaling_matrix = XMMatrixScaling(scale->x, scale->y, scale->z);

	shader_->Update(
		translation_matrix * rotation_matrix * scaling_matrix,
		App::GetSingleton()->GetScene()->GetCamera()->GetViewMatrix(),
		D3D::GetSingleton()->GetProjectionMatrix());
}

Shader* Material::GetShader()
{
	return shader_;
}