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
GameObject::GameObject(const string& name, sptr<Scene> scene)
    : Object(name),
      scene_(scene),
      parent_(nullptr),
      active_(true) {}

void GameObject::Enable() {
  active_ = true;
}

void GameObject::Disable() {
  active_ = false;
}

bool GameObject::IsActive() {
  return active_;
}

sptr<GameObject> GameObject::GetParent() {
  return parent_;
}

void GameObject::SetParent(sptr<GameObject> parent) {
  parent_ = parent;
}

sptr<Scene> GameObject::GetScene() {
  return scene_;
}

sptr<Transform> GameObject::GetTransform() {
  return GetComponent<Transform>();
}

vector<sptr<Component>> GameObject::GetComponents() const {
  vector<sptr<Component>> components;
  for (auto& it : components_)
    components.push_back(it.second);
  return components;
}

sptr<Component> GameObject::AddComponent(sptr<Component> component) {
  auto name = component->GetName();
  if (GetComponentByName(name)) {
    Log::Warning("GameObject " + GetName() + " already have " + name + " component");
    return nullptr;
  }
  return InsertComponent(component);
}

sptr<Component> GameObject::GetComponentByName(const string& name) {
  auto it = components_.find(name);
  return it != components_.end() ? it->second : nullptr;
}

sptr<Component> GameObject::InsertComponent(sptr<Component> component) {
  component->SetGameObject(d_cast<GameObject>(shared_from_this()));
  components_.insert(pair<string, sptr<Component>>(component->GetName(), component));
  return component;
}
}  // namespace voodoo