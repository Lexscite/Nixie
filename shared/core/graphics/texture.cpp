#include "../../stdafx_core.h"
#include "texture.h"

namespace vodoo
{
	Texture::Texture(ID3D11Resource* resource, ID3D11ShaderResourceView* shader_resource_view) :
		resource_(resource),
		shader_resource_view(shader_resource_view)
	{}

	Texture::~Texture()
	{
		if (resource_)
		{
			resource_->Release();
			resource_ = nullptr;
		}

		if (shader_resource_view)
		{
			shader_resource_view->Release();
			shader_resource_view = nullptr;
		}
	}

	ID3D11ShaderResourceView* Texture::GetShaderResourceView()
	{
		return shader_resource_view;
	}
}