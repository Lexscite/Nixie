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

#include "../include/voodoo/material.h"
#include "../include/voodoo/image_manager.h"

namespace voodoo {
bool Material::Init(std::string vs_path, std::string ps_path,
                    std::string texture_path, bool light) {
  shader_ = std::make_shared<Shader>();
  if (!shader_->Init(vs_path, ps_path, light)) {
    return false;
  }

  texture_ =
      std::make_shared<Texture>(ImageManager::Get().Retrieve(texture_path));

  return true;
}

bool Material::Update(const Matrix4x4<float>& world_matrix,
                      const Matrix4x4<float>& view_matrix,
                      const Matrix4x4<float>& projection_matrix) {
  if (!shader_->Update(world_matrix, view_matrix, projection_matrix,
                       texture_->srv)) {
    return false;
  }

  return true;
}
}  // namespace voodoo