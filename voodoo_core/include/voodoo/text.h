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

#ifndef VOODOO_TEXT_H_
#define VOODOO_TEXT_H_

#include "component.h"
#include "material.h"
#include "font.h"
#include "mesh.h"
#include "renderer.h"

namespace voodoo {
class Font;
struct Material;

class Text : public Component {
 public:
  Text(std::string text, std::string vs_path, std::string ps_path,
       std::string texture_path);

 private:
  virtual bool OnInit() override;

  std::shared_ptr<Mesh> GenerateMesh();
  std::vector<VertexPTN> GenerateChar(Font::CharData c, float offset);

 private:
  std::string text_;

  std::string vs_path_;
  std::string ps_path_;
  std::string texture_path_;

  std::shared_ptr<Font> font_;
  std::shared_ptr<Renderer> renderer_;
  std::shared_ptr<Mesh> mesh_;
  std::shared_ptr<Material> material_;
};
}  // namespace voodoo

#endif