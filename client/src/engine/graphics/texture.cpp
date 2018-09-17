#include "../../stdafx.h"

#include "texture.h"


namespace nixie
{
	Texture::Texture()
	{
		texture_view_ = nullptr;
	}


	Texture::~Texture()
	{
		if (texture_view_)
		{
			texture_view_->Release();
			texture_view_ = nullptr;
		}
	}


	bool Texture::Init(std::string file_path)
	{
		// Temporary file_path convertion into wide character string
		int file_path_wchar_num = MultiByteToWideChar(CP_UTF8, 0, file_path.c_str(), -1, nullptr, 0);
		wchar_t* file_path_w = new wchar_t[file_path_wchar_num];
		MultiByteToWideChar(CP_UTF8, 0, file_path.c_str(), -1, file_path_w, file_path_wchar_num);

		HRESULT hr = DirectX::CreateWICTextureFromFile(DirectXManager::Get()->GetDevice(), file_path_w, &texture_, &texture_view_);
		if (FAILED(hr))
		{
			return false;
		}

		delete[] file_path_w;

		return true;
	}


	ID3D11ShaderResourceView* Texture::GetTextureView()
	{
		return texture_view_;
	}
}