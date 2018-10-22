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

#include "../include/voodoo/game_object.h"

#include "../include/voodoo/logger.h"
#include "../include/voodoo/transform.h"

namespace voodoo {
GameObject::GameObject(const string& name, shared_ptr<Scene> scene)
    : Object(name),
      scene_(scene) {}

shared_ptr<GameObject> GameObject::GetParent() {
  return parent_;
}

void GameObject::SetParent(shared_ptr<GameObject> parent) {
  parent_ = parent;
}

shared_ptr<Scene> GameObject::GetScene() {
  return scene_;
}

shared_ptr<Transform> GameObject::GetTransform() {
  return GetComponent<Transform>();
}

vector<shared_ptr<Component>> GameObject::GetComponents() {
  vector<shared_ptr<Component>> components;
  for (auto it : components_)
    components.push_back(it.second);
  return components;
}
}  // namespace voodoo