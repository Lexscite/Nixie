#include "voodoo/texture_loader.h"

// See stb_image.h documentation for this macro explanation
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace voodoo
{
	std::shared_ptr<Texture> TextureLoader::ProcessFile(std::string file_path)
	{
		HRESULT hr;

		// Load image buffer
		int image_w, image_h, image_bpp;
		byte* image_buffer = stbi_load(
			file_path.c_str(), &image_w, &image_h, &image_bpp, 4);

		D3D11_TEXTURE2D_DESC texture_desc;
		ZeroMemory(&texture_desc, sizeof(texture_desc));
		texture_desc.Width = image_w;
		texture_desc.Height = image_h;
		texture_desc.MipLevels = 1;
		texture_desc.ArraySize = 1;
		texture_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		texture_desc.SampleDesc.Count = 1;
		texture_desc.Usage = D3D11_USAGE_DEFAULT;
		texture_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		texture_desc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA subresource_data;
		subresource_data.pSysMem = image_buffer;
		subresource_data.SysMemPitch = texture_desc.Width * 4;
		subresource_data.SysMemSlicePitch = 0;

		ID3D11Texture2D* texture;
		hr = DirectXManager::Get()->GetDevice()->CreateTexture2D(
			&texture_desc, &subresource_data, &texture);

		// Release image buffer
		stbi_image_free(image_buffer);
		if (FAILED(hr)) {
			throw std::runtime_error("Failed to create texture from memory");
		}

		D3D11_SHADER_RESOURCE_VIEW_DESC shader_resource_view_desc;
		ZeroMemory(&shader_resource_view_desc, sizeof(shader_resource_view_desc));
		shader_resource_view_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		shader_resource_view_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		shader_resource_view_desc.Texture2D.MipLevels = texture_desc.MipLevels;
		shader_resource_view_desc.Texture2D.MostDetailedMip = 0;

		ID3D11ShaderResourceView* shader_resource_view;
		hr = DirectXManager::Get()->GetDevice()->CreateShaderResourceView(
			texture, &shader_resource_view_desc, &shader_resource_view);
		if (FAILED(hr)) {
			throw std::runtime_error("Failed to create shader resource view from texture");
		}

		return std::make_shared<Texture>(texture, shader_resource_view);
	}
}