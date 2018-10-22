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

#include "../include/voodoo/shader_buffer_manager.h"

#include "../include/voodoo/logger.h"

#include <fstream>

namespace voodoo {
std::shared_ptr<ShaderBuffer> ShaderBufferManager::Load(std::string filename) {
  std::ifstream fs;

  fs.open(filename, std::ios::in | std::ios::binary);
  if (fs.fail()) {
    Log::Error("Error: Failed to open shader file ");
    throw std::runtime_error("Failed to open shader file");
  }

  fs.seekg(0, std::ios::end);
  auto size = static_cast<unsigned int>(fs.tellg());
  fs.seekg(0, std::ios::beg);

  auto buffer = std::make_shared<ShaderBuffer>(size);

  fs.read(reinterpret_cast<char*>(&buffer->data[0]), buffer->size);
  fs.close();

  return buffer;
}
}