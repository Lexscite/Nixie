// This file is part of Voodoo Engine.
//
// Voodoo Engine is free software : you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Voodoo Engine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Foobar.  If not, see <https://www.gnu.org/licenses/>.

#include "../include/voodoo/texture.h"

namespace voodoo {
Texture::Texture(std::shared_ptr<ID3D11Device> device, std::shared_ptr<Image> image) {
  HRESULT hr;

  D3D11_TEXTURE2D_DESC texture_desc;
  memset(&texture_desc, 0, sizeof(texture_desc));
  texture_desc.Width = image->width;
  texture_desc.Height = image->height;
  texture_desc.MipLevels = 1;
  texture_desc.ArraySize = 1;
  texture_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  texture_desc.SampleDesc.Count = 1;
  texture_desc.Usage = D3D11_USAGE_DEFAULT;
  texture_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
  texture_desc.CPUAccessFlags = 0;

  D3D11_SUBRESOURCE_DATA subresource_data;
  subresource_data.pSysMem = image->data;
  subresource_data.SysMemPitch = texture_desc.Width * 4;
  subresource_data.SysMemSlicePitch = 0;

  hr = device->CreateTexture2D(
      &texture_desc, &subresource_data, &texture);
  if (FAILED(hr)) {
    throw std::runtime_error("Failed to create texture from memory");
  }

  D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc;
  ZeroMemory(&srv_desc, sizeof(srv_desc));
  srv_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
  srv_desc.Texture2D.MipLevels = texture_desc.MipLevels;
  srv_desc.Texture2D.MostDetailedMip = 0;

  // Determine format by image color channels
  switch (image->channels) {
    case 1:
      srv_desc.Format = DXGI_FORMAT_R8_UNORM;
      break;
    case 2:
      srv_desc.Format = DXGI_FORMAT_R8G8_UNORM;
      break;
    default:
      srv_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
      break;
  }

  hr = device->CreateShaderResourceView(
      texture, &srv_desc, &srv);
  if (FAILED(hr)) {
    throw std::runtime_error(
        "Failed to create shader resource view from texture");
  }
}

Texture::~Texture() {
  if (texture) {
    texture->Release();
  }

  if (srv) {
    srv->Release();
  }
}
}  // namespace voodoo