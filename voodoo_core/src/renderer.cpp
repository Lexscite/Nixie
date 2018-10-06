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

#include "../include/voodoo/renderer.h"
#include "../include/voodoo/camera.h"
#include "../include/voodoo/scene.h"

namespace voodoo {
Renderer::Renderer(ID3D11Device* device, ID3D11DeviceContext* device_context)
    : device_(device), device_context_(device_context) {}

void Renderer::Render(std::shared_ptr<Mesh> mesh,
                      std::shared_ptr<Material> material) {
  auto wm = GetTransform()->CalculateWorldMatrix();
  auto vm = game_object_->GetScene()->GetCamera()->GetViewMatrix();
  auto pm = game_object_->GetScene()->GetCamera()->GetProjectionMatrix();

  if (!material->Update(wm, vm, pm)) {
    throw std::runtime_error("Failed to update material");
  }

  unsigned int stride = sizeof(mesh->GetVertices()[0]);
  unsigned int offset = 0;

  auto vertex_buffer = mesh->GetVertexBuffer();
  auto index_buffer = mesh->GetIndexBuffer();

  device_context_->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);
  device_context_->IASetIndexBuffer(index_buffer, DXGI_FORMAT_R32_UINT, 0);
  device_context_->IASetPrimitiveTopology(
      D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

  device_context_->DrawIndexed(mesh->GetIndexCount(), 0, 0);
}
}  // namespace voodoo