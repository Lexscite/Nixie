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

#include "../include/voodoo/model.h"
#include "../include/voodoo/camera.h"
#include "../include/voodoo/mesh_manager.h"
#include "../include/voodoo/renderer.h"

#include <iostream>

namespace voodoo {
Model::Model(std::string mesh_path, std::string vs_path, std::string ps_path,
             std::string texture_path)
    : mesh_path_(mesh_path),
      vs_path_(vs_path),
      ps_path_(ps_path),
      texture_path_(texture_path) {}

bool Model::OnInit() {
  mesh_ = MeshManager::Get().Retrieve(mesh_path_);
  if (!mesh_->CreateBuffers()) {
    std::cerr << "Error: Failed to initialize mesh" << std::endl;
    return false;
  }

  material_ = std::make_shared<Material>();
  if (!material_->Init(vs_path_, ps_path_, texture_path_, true)) {
    std::cerr << "Error: Failed to initialize material" << std::endl;
    return false;
  }

  return true;
}

bool Model::OnUpdate() {
  auto x = GetScene();
  auto y = x->GetCamera();
  auto z = y->GetViewMatrix();

  auto world_matrix = GetTransform()->CalculateWorldMatrix();
  auto view_matrix = GetScene()->GetCamera()->GetViewMatrix();
  auto projection_matrix = GetScene()->GetCamera()->GetProjectionMatrix();

  if (!material_->Update(world_matrix, view_matrix, projection_matrix)) {
    return false;
  }

  Renderer::Get().RenderMesh(mesh_);

  return true;
}
}  // namespace voodoo