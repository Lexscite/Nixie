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
sptr<GameObject> Component::GetGameObject() {
  return game_object_;
}

void Component::SetGameObject(sptr<GameObject> game_object) {
  game_object_ = game_object;
}

sptr<GameObject> Component::GetParent() const {
  return game_object_->GetParent();
}

void Component::SetParent(sptr<GameObject> parent) {
  game_object_->SetParent(parent);
}

sptr<Scene> Component::GetScene() {
  return game_object_->GetScene();
}

sptr<Transform> Component::GetTransform() {
  return game_object_->GetTransform();
}

sptr<Component> Component::AddComponent(sptr<Component> component) {
  return game_object_->AddComponent(component);
}

void Component::SetName(string name) {
  name_ = name;
}
}  // namespace voodoo