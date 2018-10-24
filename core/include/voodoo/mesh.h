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

#ifndef VOODOO_MESH_H_
#define VOODOO_MESH_H_

#include "vertex.h"

#include <vector>

namespace voodoo {
struct MeshSubset {
  MeshSubset()
      : id(-1),
        vertex_start(0),
        vertex_count(0),
        face_start(0),
        face_count(0) {}

  MeshSubset(uint id, uint vertex_start, uint vertex_count,
             uint face_start, uint face_count)
      : id(id),
        vertex_start(vertex_start),
        vertex_count(vertex_count),
        face_start(face_start),
        face_count(face_count) {}

  uint id;
  uint vertex_start;
  uint vertex_count;
  uint face_start;
  uint face_count;
};

struct Mesh {
 public:
  Mesh()
      : vertices(),
        vertex_count(0),
        indices(),
        index_count(0) {}

  Mesh(vector<vertex_ptn> vertices)
      : vertices(vertices),
        indices(),
        vertex_count(uint(vertices.size())),
        index_count(vertex_count) {
    for (uint i = 0; i < index_count; i++)
      indices.push_back(i);
  }

  Mesh(const Mesh& other)
      : vertices(other.vertices),
        vertex_count(other.vertex_count),
        indices(other.indices),
        index_count(other.index_count) {}

 public:
  vector<vertex_ptn> vertices;
  uint vertex_count;

  vector<uint> indices;
  uint index_count;
};
}  // namespace voodoo

#endif  // VOODOO_MESH_H_