#include "../stdafx_core.h"
#include "shader_loader.h"

namespace vodoo
{
	std::shared_ptr<Shader> ShaderLoader::ProcessFile(std::string file_path)
	{
		return std::make_shared<Shader>();
	}
}