#include "material.h"

namespace Nixie
{
	Material::Material() :
		shader(nullptr),
		texture(nullptr) {}

	void Material::OnInit()
	{
		LoadTexture(L"../data/textures/placeholder.jpg");

		shader = new Shader;
		shader->Init(L"../data/shaders/default_vs.hlsl.", L"../data/shaders/default_ps.hlsl.");
		shader->SetTexture(texture->GetTextureView());
	}

	void Material::OnUpdate()
	{
		shader->Update(GetTransform()->CalculateWorldMatrix());
	}

	bool Material::LoadTexture(const wchar_t* file_path)
	{
		texture = new Texture;
		if (!texture->Init(file_path))
			return false;

		return true;
	}

	Shader* Material::GetShader()
	{
		return shader;
	}
}