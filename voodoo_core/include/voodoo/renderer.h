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

#ifndef VOODOO_RENDERER_H_
#define VOODOO_RENDERER_H_

#include "component.h"
#include "material.h"
#include "mesh.h"

namespace voodoo {
class Renderer : public Component {
 public:
  Renderer(std::shared_ptr<ID3D11Device> device,
           std::shared_ptr<ID3D11DeviceContext> device_context);

  bool CreateBuffers();
  bool InitMaterial(std::string texture_path, std::string vs_path,
                    std::string ps_path, bool light);

  void SetMesh(std::shared_ptr<Mesh> mesh);
  void SetMaterial(std::shared_ptr<Material> material);

  std::shared_ptr<Mesh> GetMesh();
  std::shared_ptr<Material> GetMaterial();
  ID3D11Buffer* GetVertexBuffer();
  ID3D11Buffer* GetIndexBuffer();

 private:
  bool CreateVertexBuffer();
  bool CreateIndexBuffer();

 private:
  std::shared_ptr<Mesh> mesh_;
  std::shared_ptr<Material> material_;

  std::shared_ptr<ID3D11Device> device_;
  std::shared_ptr<ID3D11DeviceContext> device_context_;

  ID3D11Buffer* v_buffer_;
  ID3D11Buffer* i_buffer_;
};
}  // namespace voodoo

#endif