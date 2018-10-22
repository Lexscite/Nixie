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

#include "../include/voodoo/mesh_filter.h"

namespace voodoo {
shared_ptr<Mesh> MeshFilter::GetMesh() {
  return mesh_;
}

void MeshFilter::SetMesh(shared_ptr<Mesh> mesh) {
  mesh_ = mesh;
}

shared_ptr<Material> MeshFilter::GetMaterial() {
  return material_;
}

void MeshFilter::SetMaterial(shared_ptr<Material> material) {
  material_ = material;
}

void MeshFilter::Start() {
  renderer_ = GetComponent<Renderer>();
  renderer_->SetMesh(mesh_);
  renderer_->SetMaterial(material_);
}
}  // namespace voodoo