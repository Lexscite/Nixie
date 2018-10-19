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
#include "../include/voodoo/image_manager.h"

namespace voodoo {
Renderer::Renderer(std::shared_ptr<ID3D11Device> device,
                   std::shared_ptr<ID3D11DeviceContext> device_context)
    : device_(device),
      device_context_(device_context) {}

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
}  // namespace voodoo