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

namespace voodoo {
Renderer::Renderer()
    : device_(DirectXManager::Get()->GetDevice()),
      device_context_(DirectXManager::Get()->GetDeviceContext()) {}

Renderer& Renderer::Get() {
  static Renderer instance;
  return instance;
}

void Renderer::RenderMesh(std::shared_ptr<Mesh> mesh) {
  unsigned int stride = sizeof(VertexPTN);
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