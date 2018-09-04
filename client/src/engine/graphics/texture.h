#ifndef TEXTURE_H
#define TEXTURE_H

#pragma once

#include "d3d.h"

namespace Nixie
{
	class Texture
	{
	public:
		Texture();

		bool Init(const wchar_t* file_path);
		void Release();

		ID3D11ShaderResourceView* GetTextureView();

	private:
		ID3D11Resource * texture_;
		ID3D11ShaderResourceView* texture_view_;
	};
}

#endif
