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

#ifndef VOODOO_MATERIAL_H_
#define VOODOO_MATERIAL_H_

#include "shader.h"
#include "texture.h"

#include <memory>
#include <string>

namespace voodoo {
class Material {
 public:
  bool Init(std::string vs_path, std::string ps_path, std::string texture_path,
            bool light);
  bool Update(const Matrix4x4<float>& world_matrix,
              const Matrix4x4<float>& view_matrix,
              const Matrix4x4<float>& projection_matrix);

 private:
  std::shared_ptr<Shader> shader_;
  std::shared_ptr<Texture> texture_;
};
}  // namespace voodoo

#endif