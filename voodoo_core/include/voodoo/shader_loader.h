#ifndef VOODOO_SHADER_LOADER_H_
#define VOODOO_SHADER_LOADER_H_

#include "resource_loader.h"
#include "shader.h"

namespace voodoo
{
	class ShaderLoader : public ResourceLoader<Shader>
	{
	public:
		// Temporal singleton
		static ShaderLoader& Get()
		{
			static ShaderLoader instance;
			return instance;
		}

	private:
		virtual std::shared_ptr<Shader> ProcessFile(std::string file_path) override;
	};
}

#endif