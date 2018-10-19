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

#ifndef VOODOO_MESH_H_
#define VOODOO_MESH_H_

#include "vertex.h"

#include <vector>

namespace voodoo {
struct Mesh {
 public:
  Mesh() : vertices(),
           vertex_count(0),
           indices(),
           index_count(0) {}

  Mesh(std::vector<VertexPTN> v) : vertices(v),
                                   indices(),
                                   vertex_count(unsigned long(v.size())),
                                   index_count(vertex_count) {
    for (unsigned long i = 0; i < index_count; i++)
      indices.push_back(i);
  }

 public:
  unsigned long vertex_count;
  unsigned long index_count;

  std::vector<VertexPTN> vertices;
  std::vector<unsigned long> indices;
};
}  // namespace voodoo

#endif