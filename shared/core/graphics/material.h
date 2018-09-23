#ifndef NIXIE_MATERIAL_H_
#define NIXIE_MATERIAL_H_

#include "texture.h"
#include "shader.h"

namespace nixie
{
	class Material
	{
	public:
		bool Init(std::string vs_path, std::string ps_path, std::string texture_path, bool light);
		bool Update(
			const Matrix4x4<float>& world_matrix,
			const Matrix4x4<float>& view_matrix,
			const Matrix4x4<float>& projection_matrix);

	private:
		std::shared_ptr<Shader> shader_;
		std::shared_ptr<Texture> texture_;
	};
}

#endif