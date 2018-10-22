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

#include "behavior.h"
#include "font.h"
#include "material.h"
#include "mesh.h"
#include "renderer.h"

namespace voodoo {
class Font;
struct Material;

class Text : public Behavior {
 public:
  string GetText();
  void SetText(const string& text);

  shared_ptr<Font> GetFont();
  void SetFont(shared_ptr<Font> font);

  shared_ptr<Material> GetMaterial();
  void SetMaterial(shared_ptr<Material> material);

 private:
  virtual void Start() override;

  shared_ptr<Mesh> GenerateMesh();
  vector<VertexPTN> GenerateChar(Font::CharData c, const float& offset);

 private:
  string text_;

  string vs_path_;
  string ps_path_;
  string texture_path_;

  shared_ptr<Font> font_;
  shared_ptr<Renderer> renderer_;
  shared_ptr<Mesh> mesh_;
  shared_ptr<Material> material_;
};
}  // namespace voodoo

#endif