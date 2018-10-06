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

#ifndef VOODOO_RENDERER_H_
#define VOODOO_RENDERER_H_

#include "directx_manager.h"
#include "mesh.h"

namespace voodoo {
class Renderer {
 public:
  static Renderer& Get();

  void RenderMesh(std::shared_ptr<Mesh> mesh);

 private:
  Renderer();

  ID3D11Device* device_;
  ID3D11DeviceContext* device_context_;
};
}  // namespace voodoo

#endif