#include "material.h"

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
	shader_->Render();
}

Shader* Material::GetShader()
{
	return shader_;
}