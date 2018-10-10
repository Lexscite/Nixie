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

#include "../include/voodoo/text_mesh.h"

namespace voodoo {
TextMesh::TextMesh(std::shared_ptr<Font> font) : font_(font) {}

void TextMesh::Generate(std::string text) {
  v_.clear();
  i_.clear();

  float offset = 0;

  for (auto& c : text) {
    auto c_data = font_->GetCharData(c);
    auto v = GenerateChar(c_data, offset);
    v_.insert(v_.begin(), v.begin(), v.end());
    offset += c_data.width;
  }

  v_count_ = i_count_ = static_cast<unsigned long>(v_.size());

  for (unsigned long i = 0; i < i_count_; i++) {
    i_.push_back(i);
  }

  CreateVertexBuffer();
  CreateIndexBuffer();
}

std::vector<VertexPTN> TextMesh::GenerateChar(Font::CharData c, float offset) {
  float t_width = font_->GetWidth();
  float t_height = font_->GetHeight();

  float t_right = c.x / t_width;
  float t_left = (c.x + c.width) / t_width;
  float t_bottom = c.y / t_height;
  float t_top = (c.y + c.height) / t_height;

  auto v_lt = VertexPTN(Vector3f(-offset, 0, 0),
                        Vector2f(t_left, t_top),
                        Vector3f(0.0f, 0.0f, 1.0f));

  auto v_rt = VertexPTN(Vector3f(-offset + c.width, 0, 0),
                        Vector2f(t_right, t_top),
                        Vector3f(0.0f, 0.0f, 1.0f));

  auto v_lb = VertexPTN(Vector3f(-offset, c.height, 0),
                        Vector2f(t_left, t_bottom),
                        Vector3f(0.0f, 0.0f, 1.0f));

  auto v_rb = VertexPTN(Vector3f(-offset + c.width, c.height, 0),
                        Vector2f(t_right, t_bottom),
                        Vector3f(0.0f, 0.0f, 1.0f));

  return std::vector<VertexPTN>({v_lt, v_rb, v_lb, v_lt, v_rt, v_rb});
}
}  // namespace voodoo