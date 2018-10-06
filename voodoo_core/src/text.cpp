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
  renderer_ = std::static_pointer_cast<Renderer>(game_object_->GetComponent("Renderer"));

  auto font = std::make_shared<Font>();
  if (!font->Init()) {
    return false;
  }

  mesh_ = std::make_shared<TextMesh>(font);
  mesh_->Generate(text_);

  material_ = std::make_shared<Material>();
  if (!material_->Init(vs_path_, ps_path_, texture_path_, false)) {
    return false;
  }

  return true;
}

bool Text::OnUpdate() {
  renderer_->Render(mesh_, material_);
  return true;
}
}  // namespace voodoo