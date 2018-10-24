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

#ifndef VOODOO_MATERIAL_H_
#define VOODOO_MATERIAL_H_

#include "shader.h"
#include "texture.h"

#include <memory>
#include <string>

namespace voodoo {
struct Material {
 public:
  Material(sptr<Shader> shader, sptr<Texture> texture)
      : shader(shader),
        texture(texture) {}

  Material(const Material& other)
      : Material(other.shader, other.texture) {}

 public:
  sptr<Shader> shader;
  sptr<Texture> texture;
};
}  // namespace voodoo

#endif