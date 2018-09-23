#ifndef NIXIE_TEXTURE_LOADER_H_
#define NIXIE_TEXTURE_LOADER_H_

#include "resource_loader.h"
#include "graphics/texture.h"

namespace nixie
{
	class TextureLoader : public ResourceLoader<Texture>
	{
	public:
		// Temporal singleton
		static TextureLoader& Get()
		{
			static TextureLoader instance;
			return instance;
		}

	private:
		virtual std::shared_ptr<Texture> ProcessFile(std::string file_path) override;
	};
}

#endif