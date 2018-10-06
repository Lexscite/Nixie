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

#include "directx_manager.h"
#include "vertex.h"

#include <memory>
#include <vector>

namespace voodoo {
class Mesh {
 public:
  Mesh();
  Mesh(std::vector<VertexPTN> v);

  bool CreateBuffers();

  unsigned long GetVertexCount();
  unsigned long GetIndexCount();

  std::vector<VertexPTN> GetVertices();
  std::vector<unsigned long> GetIndices();

  ID3D11Buffer* GetVertexBuffer();
  ID3D11Buffer* GetIndexBuffer();

 protected:
  bool CreateVertexBuffer();
  bool CreateIndexBuffer();

 protected:
  std::shared_ptr<ID3D11Device> device_;
  std::shared_ptr<ID3D11DeviceContext> device_context_;

  unsigned long v_count_;
  unsigned long i_count_;

  std::vector<VertexPTN> v_;
  std::vector<unsigned long> i_;

  ID3D11Buffer* vertex_buffer_;
  ID3D11Buffer* index_buffer_;
};
}  // namespace voodoo

#endif