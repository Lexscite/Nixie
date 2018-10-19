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
#include "../include/voodoo/component.h"
#include "../include/voodoo/logger.h"
#include "../include/voodoo/transform.h"

namespace voodoo {
GameObject::GameObject(std::string name, std::shared_ptr<Scene> scene)
    : name_(name),
      scene_(scene),
      parent_(nullptr),
      transform_(new Transform(std::shared_ptr<GameObject>(this))) {}

std::string GameObject::GetName() { return name_; }
std::shared_ptr<Scene> GameObject::GetScene() { return scene_; }
std::shared_ptr<GameObject> GameObject::GetParent() { return parent_; }
std::shared_ptr<Transform> GameObject::GetTransform() { return transform_; }

std::vector<std::shared_ptr<Component>> GameObject::GetComponents() {
  std::vector<std::shared_ptr<Component>> result;
  for (auto it : components_) {
    result.push_back(it.second);
  }

  return result;
}
}  // namespace voodoo