#include "material.h"

Material::Material()
{
	shader_ = nullptr;
	mesh_ = nullptr;
}

void Material::AfterInit()
{
	mesh_ = static_cast<Mesh*>(GetGameObject()->GetComponent("Mesh"));
}

void Material::OnInit()
{
	shader_ = new Shader;
	shader_->Init();
}

void Material::OnUpdate()
{
	shader_->Render(mesh_->GetIndexCount());
}

Shader* Material::GetShader()
{
	return shader_;
}