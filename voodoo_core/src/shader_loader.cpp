#include "voodoo/shader_loader.h"

namespace voodoo
{
	std::shared_ptr<Shader> ShaderLoader::ProcessFile(std::string file_path)
	{
		return std::make_shared<Shader>();
	}
}