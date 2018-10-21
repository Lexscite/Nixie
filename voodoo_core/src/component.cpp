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

#include "../include/voodoo/component.h"

namespace voodoo {
std::shared_ptr<Scene> Component::GetScene() {
  return game_object_->GetScene();
}

std::shared_ptr<GameObject> Component::GetGameObject() {
  return game_object_;
}

std::shared_ptr<GameObject> Component::GetParent() {
  return game_object_->GetParent();
}

std::shared_ptr<Transform> Component::GetTransform() {
  return game_object_->GetTransform();
}

void Component::SetGameObject(std::shared_ptr<GameObject> go) {
  game_object_ = go;
}
}  // namespace voodoo