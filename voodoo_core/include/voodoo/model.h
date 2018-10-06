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

#ifndef VOODOO_MODEL_H_
#define VOODOO_MODEL_H_

#include "component.h"
#include "material.h"
#include "mesh.h"

namespace voodoo {
class Model : public Component {
 public:
  Model(std::string mesh_file_path, std::string vs_shader_path,
        std::string ps_shader_path, std::string texture_path);

 private:
  virtual bool OnInit() override;
  virtual bool OnUpdate() override;

 private:
  std::string mesh_path_;
  std::string vs_path_;
  std::string ps_path_;
  std::string texture_path_;

  std::shared_ptr<Mesh> mesh_;
  std::shared_ptr<Material> material_;
};
}  // namespace voodoo

#endif