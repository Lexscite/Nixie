#ifndef vodoo_SHADER_LOADER_H_
#define vodoo_SHADER_LOADER_H_

#include "resource_loader.h"
#include "graphics/shader.h"

namespace vodoo
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