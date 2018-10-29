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
  sptr<Mesh> GetMesh() const;
  void SetMesh(sptr<Mesh> mesh);

  sptr<Material> GetMaterial() const;
  void SetMaterial(sptr<Material> material);

 private:
  sptr<Mesh> mesh_;
  sptr<Material> material_;
};
}  // namespace voodoo

#endif  // VOODOO_RENDERER_H_