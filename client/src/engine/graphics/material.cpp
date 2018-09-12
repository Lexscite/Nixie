#include "../../stdafx.h"

#include "material.h"


namespace Nixie
{
	bool Material::Init(std::string vs_path, std::string ps_path, std::string texture_path, bool light)
	{
		shader_ = std::make_unique<Shader>();
		if (!shader_->Init(vs_path, ps_path, light))
		{
			return false;
		}

		texture_ = std::make_unique<Texture>();
		if (!texture_->Init(texture_path))
		{
			return false;
		}

		return true;
	}


	bool Material::Update(const Matrix4x4<float>& world_matrix)
	{
		if (!shader_->Update(world_matrix, texture_->GetTextureView()))
		{
			return false;
		}

		return true;
	}
}