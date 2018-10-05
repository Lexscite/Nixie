#include "voodoo/image_manager.h"

// See stb_image.h documentation for this macro explanation.
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace voodoo
{
	std::shared_ptr<Image> ImageManager::Load(std::string filename)
	{
		// Image data will always be stored in 4-chanelled format
		// but despite this actual channels count will be stored
		// as member value.
		int width, height, channels;
		unsigned char* data = stbi_load(
			filename.c_str(), &width, &height, &channels, 4);
		if (data == NULL) {
			throw std::runtime_error("Failed to read image file: \"" + filename + "\"");
		}
		auto image = std::make_shared<Image>(width, height, channels, data);

		return image;
	}
}