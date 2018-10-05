#ifndef VOODOO_IMAGE_MANAGER_H_
#define VOODOO_IMAGE_MANAGER_H_

#include "asset_manager.h"
#include "image.h"

namespace voodoo
{
	class ImageManager : public AssetManager<Image>
	{
	public:
		// Temporal singleton
		static ImageManager& Get()
		{
			static ImageManager instance;
			return instance;
		}

	private:
		virtual std::shared_ptr<Image> Load(std::string filename) override;
	};
}

#endif