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

#ifndef VOODOO_SHADER_BUFFER_MANAGER_H_
#define VOODOO_SHADER_BUFFER_MANAGER_H_

#include "asset_manager.h"

#include "shader.h"

namespace voodoo{
class ShaderBufferManager : public AssetManager<ShaderBuffer> {
public:
  // Temporal singleton
  static ShaderBufferManager& Get() {
    static ShaderBufferManager instance;
    return instance;
  }

private:
  virtual std::shared_ptr<ShaderBuffer> Load(std::string filename) override;
};
}

#endif