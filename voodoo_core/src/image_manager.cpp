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
// along with Voodoo Engine.  If not, see <https://www.gnu.org/licenses/>.

#include "../include/voodoo/image_manager.h"

// See stb_image.h documentation for this macro explanation.
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace voodoo {
std::shared_ptr<Image> ImageManager::Load(std::string filename) {
  // Image data will always be stored in 4-chanelled format
  // but despite this actual channels count will be stored
  // as member value.
  int width, height, channels;
  unsigned char* data =
      stbi_load(filename.c_str(), &width, &height, &channels, 4);
  if (data == NULL) {
    throw std::runtime_error("Failed to read image file: \"" + filename + "\"");
  }
  auto image = std::make_shared<Image>(width, height, channels, data);

  return image;
}
}  // namespace voodoo