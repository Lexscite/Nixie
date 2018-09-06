#ifndef NIXIE_MATERIAL_H_
#define NIXIE_MATERIAL_H_

#pragma once
#include "texture.h"
#include "shader.h"


namespace Nixie
{
	class Material
	{
	public:
		bool Init(std::string vs_path, std::string ps_path, std::string texture_path);
		bool Update(DirectX::SimpleMath::Matrix world_matrix);

	private:
		std::unique_ptr<Shader> shader_;
		std::unique_ptr<Texture> texture_;
	};
}

#endif