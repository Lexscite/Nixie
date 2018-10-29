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
sptr<ShaderBuffer> ShaderBufferManager::Load(const string& filename) {
  using namespace std;
  ifstream fs;
  fs.open(filename, ios::in | ios::binary);
  if (fs.fail()) {
    Log::Error("Error: Failed to open shader file ");
    throw runtime_error("Failed to open shader file");
  }

  fs.seekg(0, ios::end);
  auto size = static_cast<uint>(fs.tellg());
  fs.seekg(0, ios::beg);

  auto buffer = make_shared<ShaderBuffer>(size);

  fs.read(reinterpret_cast<char*>(&buffer->data[0]), buffer->size);
  fs.close();

  return buffer;
}
}