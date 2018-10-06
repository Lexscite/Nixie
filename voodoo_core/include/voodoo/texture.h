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

#ifndef VOODOO_TEXTURE_H_
#define VOODOO_TEXTURE_H_

#include "directx_manager.h"
#include "image.h"

#include <stdexcept>

namespace voodoo {
struct Texture {
 public:
  Texture(std::shared_ptr<Image> image);
  ~Texture();

 public:
  ID3D11Texture2D* texture;
  ID3D11ShaderResourceView* srv;
};
}  // namespace voodoo

#endif
