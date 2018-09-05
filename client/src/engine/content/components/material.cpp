#include "../../../stdafx.h"

#include "material.h"

namespace Nixie
{
	Material::Material(const wchar_t* texture_path) :
		texture_path(texture_path),
		shader(nullptr),
		texture(nullptr) {}

	void Material::OnInit()
	{
		LoadTexture();

		shader = new Shader;
		shader->Init("../data/shaders/default_vs.cso", "../data/shaders/default_ps.cso");
	}

	void Material::OnUpdate()
	{
		shader->SetTexture(texture->GetTextureView());
		shader->Update(GetTransform()->CalculateWorldMatrix());
	}

	bool Material::LoadTexture()
	{
		texture = new Texture;
		if (!texture->Init(texture_path))
			return false;

		return true;
	}

	Shader* Material::GetShader()
	{
		return shader;
	}
}