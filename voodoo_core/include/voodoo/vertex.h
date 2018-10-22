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

#ifndef VOODOO_VERTEX_H_
#define VOODOO_VERTEX_H_

#include "math.h"

namespace voodoo {
struct VertexP {
  VertexP() = default;

  VertexP(const vec3<float>& position) : position(position) {}

  vec3<float> position;
};

struct VertexPT : public VertexP {
  VertexPT() = default;

  VertexPT(const vec3<float>& position, const vec2<float>& texture)
      : VertexP(position), texture(texture) {}

  vec2<float> texture;
};

struct VertexPTN : public VertexPT {
  VertexPTN() = default;

  VertexPTN(const vec3<float>& position, const vec2<float>& texture,
            const vec3<float>& normal)
      : VertexPT(position, texture), normal(normal) {}

  vec3<float> normal;
};
}  // namespace voodoo

#endif