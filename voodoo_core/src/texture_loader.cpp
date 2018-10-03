#include "voodoo/texture_loader.h"

// TODO: Get rid of this shoot for cross-platform solution
#include <WICTextureLoader.h>

namespace voodoo
{
	std::shared_ptr<Texture> TextureLoader::ProcessFile(std::string file_path)
	{
		// TODO: Also get rid of this shoot
		int file_path_wchar_num = MultiByteToWideChar(CP_UTF8, 0, file_path.c_str(), -1, nullptr, 0);
		wchar_t* file_path_w = new wchar_t[file_path_wchar_num];
		MultiByteToWideChar(CP_UTF8, 0, file_path.c_str(), -1, file_path_w, file_path_wchar_num);

		ID3D11Resource* resource;
		ID3D11ShaderResourceView* shader_resource_view;

		HRESULT hr = DirectX::CreateWICTextureFromFile(
			DirectXManager::Get()->GetDevice(),
			file_path_w,
			&resource,
			&shader_resource_view);
		delete[] file_path_w;
		if (FAILED(hr)) {
			resource->Release();
			shader_resource_view->Release();
			throw std::runtime_error("Failed to process texture file: \"" + file_path + "\"");
		}

		auto texture = std::make_shared<Texture>(resource, shader_resource_view);

		return texture;
	}
}