#include "texture.h"

Texture::Texture()
{
	texture_view_ = nullptr;
}

bool Texture::Init(const wchar_t* file_path)
{
	HRESULT hr;
	
	hr = CreateWICTextureFromFile(
		D3D::GetSingleton()->GetDevice(),
		file_path,
		&texture_,
		&texture_view_);
	if (FAILED(hr))
		return false;

	return true;
}

void Texture::Release()
{
	if (texture_view_)
		safe_release(texture_view_);
}

ID3D11ShaderResourceView* Texture::GetTextureView()
{
	return texture_view_;
}