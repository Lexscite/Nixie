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

#ifndef VOODOO_FONT_MESH_H_
#define VOODOO_FONT_MESH_H_

#include "font.h"
#include "mesh.h"

namespace voodoo {
class TextMesh : public Mesh {
 public:
  TextMesh(std::shared_ptr<Font> font);

  void Generate(std::string text);

 private:
  std::vector<VertexPTN> GenerateChar(Font::CharData c, float offset);

 private:
  std::shared_ptr<Font> font_;
};
}  // namespace voodoo

#endif