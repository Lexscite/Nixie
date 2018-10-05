#ifndef VOODOO_TEXTURE_H_
#define VOODOO_TEXTURE_H_

#include "directx_manager.h"
#include "image.h"

#include <stdexcept>

namespace voodoo
{
	struct Texture
	{
	public:
		Texture(std::shared_ptr<Image> image);
		~Texture();

	public:
		ID3D11Texture2D* texture;
		ID3D11ShaderResourceView* srv;
	};
}

#endif
