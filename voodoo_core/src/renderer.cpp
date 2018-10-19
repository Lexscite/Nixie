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

#include "../include/voodoo/renderer.h"
#include "../include/voodoo/camera.h"
#include "../include/voodoo/image_manager.h"
#include "../include/voodoo/scene.h"

namespace voodoo {
Renderer::Renderer(std::shared_ptr<ID3D11Device> device,
                   std::shared_ptr<ID3D11DeviceContext> device_context)
    : device_(device),
      device_context_(device_context),
      i_buffer_(),
      v_buffer_() {}

bool Renderer::CreateBuffers() {
  if (!CreateVertexBuffer()) {
    Log::Error("Failed to create vertex buffer");
    return false;
  }
  if (!CreateIndexBuffer()) {
    Log::Error("Failed to create index buffer");
    return false;
  }

  return true;
}

bool Renderer::InitMaterial(std::string texture_path, std::string vs_path,
                            std::string ps_path, bool light) {
  material_->shader = std::make_shared<Shader>(device_, device_context_);
  if (!material_->shader->Init(vs_path, ps_path, light)) {
    return false;
  }

  material_->texture = std::make_shared<Texture>(
      device_,
      ImageManager::Get().Retrieve(texture_path));

  return true;
}

void Renderer::SetMesh(std::shared_ptr<Mesh> mesh) {
  mesh_ = mesh;
}

void Renderer::SetMaterial(std::shared_ptr<Material> material) {
  material_ = material;
}

std::shared_ptr<Mesh> Renderer::GetMesh() { return mesh_; }
std::shared_ptr<Material> Renderer::GetMaterial() { return material_; }

ID3D11Buffer* Renderer::GetVertexBuffer() { return v_buffer_; }
ID3D11Buffer* Renderer::GetIndexBuffer() { return i_buffer_; }

bool Renderer::CreateVertexBuffer() {
  unsigned int byte_width = sizeof(mesh_->vertices[0]) * mesh_->vertex_count;

  D3D11_BUFFER_DESC vertex_buffer_desc;
  vertex_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
  vertex_buffer_desc.ByteWidth = byte_width;
  vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  vertex_buffer_desc.CPUAccessFlags = 0;
  vertex_buffer_desc.MiscFlags = 0;
  vertex_buffer_desc.StructureByteStride = 0;

  D3D11_SUBRESOURCE_DATA vertex_buffer_data;
  vertex_buffer_data.pSysMem = mesh_->vertices.data();
  vertex_buffer_data.SysMemPitch = 0;
  vertex_buffer_data.SysMemSlicePitch = 0;

  HRESULT hr = device_->CreateBuffer(&vertex_buffer_desc,
                                     &vertex_buffer_data,
                                     &v_buffer_);
  if (FAILED(hr)) {
    return false;
  }

  return true;
}

bool Renderer::CreateIndexBuffer() {
  unsigned int byte_width = sizeof(mesh_->indices[0]) * mesh_->index_count;

  D3D11_BUFFER_DESC index_buffer_desc;
  index_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
  index_buffer_desc.ByteWidth = byte_width;
  index_buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
  index_buffer_desc.CPUAccessFlags = 0;
  index_buffer_desc.MiscFlags = 0;
  index_buffer_desc.StructureByteStride = 0;

  D3D11_SUBRESOURCE_DATA index_data;
  index_data.pSysMem = mesh_->indices.data();
  index_data.SysMemPitch = 0;
  index_data.SysMemSlicePitch = 0;

  HRESULT hr =
      device_->CreateBuffer(&index_buffer_desc,
                            &index_data,
                            &i_buffer_);
  if (FAILED(hr)) {
    return false;
  }

  return true;
}
}  // namespace voodoo