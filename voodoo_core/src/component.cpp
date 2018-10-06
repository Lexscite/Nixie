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

#include "../include/voodoo/component.h"

namespace voodoo {
bool Component::Init(std::shared_ptr<GameObject> game_object) {
  game_object_ = game_object;

  if (!OnInit()) {
    return false;
  }

  return true;
}

bool Component::OnInit() { return true; }

bool Component::Update() {
  if (!OnUpdate()) {
    return false;
  }

  return true;
}

bool Component::OnUpdate() { return true; }

std::string Component::GetName() {
  // TODO: Very strange stuff going on here so get it the hell out
  return std::string(typeid(*shared_from_this()).name()).erase(0, 14);
}

std::shared_ptr<Scene> Component::GetScene() {
  return game_object_->GetScene();
}

std::shared_ptr<GameObject> Component::GetGameObject() { return game_object_; }

std::shared_ptr<Transform> Component::GetTransform() {
  return game_object_->GetTransform();
}
}  // namespace voodoo