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

#include "../include/voodoo/text.h"
#include "../include/voodoo/camera.h"

namespace voodoo {
Text::Text(std::string text, std::string vs_path, std::string ps_path,
           std::string texture_path)
    : text_(text),
      vs_path_(vs_path),
      ps_path_(ps_path),
      texture_path_(texture_path) {}

bool Text::OnInit() {
  using namespace std;
  renderer_ = GetComponent<Renderer>();

  font_ = make_shared<Font>();
  if (!font_->Init()) {
    return false;
  }

  mesh_ = GenerateMesh();
  renderer_->SetMesh(mesh_);
  if (!renderer_->CreateBuffers()) {
    return false;
  }

  material_ = make_shared<Material>();
  renderer_->SetMaterial(material_);
  if (!renderer_->InitMaterial(texture_path_, vs_path_, ps_path_, true)) {
    Log::Error("Failed to initialize material");
    return false;
  }

  return true;
}

std::shared_ptr<Mesh> Text::GenerateMesh() {
  using namespace std;
  vector<VertexPTN> vs;
  float offset = 0;
  for (auto& c : text_) {
    auto c_data = font_->GetCharData(c);
    auto v = GenerateChar(c_data, offset);
    vs.insert(vs.begin(), v.begin(), v.end());
    offset += c_data.width;
  }
  return make_shared<Mesh>(vs);
}

std::vector<VertexPTN> Text::GenerateChar(Font::CharData c, float offset) {
  using namespace std;
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

  return vector<VertexPTN>({v_lt, v_rb, v_lb, v_lt, v_rt, v_rb});
}
}  // namespace voodoo