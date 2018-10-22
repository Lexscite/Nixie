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

#include "../include/voodoo/text.h"

namespace voodoo {
string Text::GetText() {
  return text_;
}

void Text::SetText(const string& text) {
  text_ = text;
}

shared_ptr<Font> Text::GetFont() {
  return font_;
}

void Text::SetFont(shared_ptr<Font> font) {
  font_ = font;
}

shared_ptr<Material> Text::GetMaterial() {
  return material_;
}

void Text::SetMaterial(shared_ptr<Material> material) {
  material_ = material;
}

void Text::Start() {
  mesh_ = GenerateMesh();
  renderer_ = GetComponent<Renderer>();
  renderer_->SetMesh(mesh_);
  renderer_->SetMaterial(material_);
}

shared_ptr<Mesh> Text::GenerateMesh() {
  vector<VertexPTN> vs;
  float offset = 0;

  for (auto& c : text_) {
    auto c_data = font_->GetCharData(c);
    auto v = GenerateChar(c_data, offset);
    vs.insert(vs.begin(), v.begin(), v.end());
    offset += c_data.width;
  }

  return std::make_shared<Mesh>(vs);
}

vector<VertexPTN> Text::GenerateChar(Font::CharData c, const float& offset) {
  float width = font_->GetWidth();
  float height = font_->GetHeight();

  float right = c.x / width;
  float left = (c.x + c.width) / width;
  float bottom = c.y / height;
  float top = (c.y + c.height) / height;

  auto v_lt = VertexPTN(vec3f(-offset, 0, 0),
                        vec2f(left, top),
                        vec3f(0.0f, 0.0f, 1.0f));

  auto v_rt = VertexPTN(vec3f(-offset + c.width, 0, 0),
                        vec2f(right, top),
                        vec3f(0.0f, 0.0f, 1.0f));

  auto v_lb = VertexPTN(vec3f(-offset, c.height, 0),
                        vec2f(left, bottom),
                        vec3f(0.0f, 0.0f, 1.0f));

  auto v_rb = VertexPTN(vec3f(-offset + c.width, c.height, 0),
                        vec2f(right, bottom),
                        vec3f(0.0f, 0.0f, 1.0f));

  return vector<VertexPTN>({v_lt, v_rb, v_lb, v_lt, v_rt, v_rb});
}
}  // namespace voodoo