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

#ifndef VOODOO_GAME_OBJECT_H_
#define VOODOO_GAME_OBJECT_H_

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace voodoo {
class Scene;
class Component;
class Transform;

class GameObject final : public std::enable_shared_from_this<GameObject> {
 public:
  GameObject(std::string name);

  bool Init(std::shared_ptr<Scene> scene);
  bool Update();

  bool AddComponent(std::shared_ptr<Component> new_component);
  std::shared_ptr<Component> GetComponent(std::string name);
  std::vector<std::shared_ptr<Component>> GetComponents();

  std::string GetName() { return name_; }
  std::shared_ptr<Scene> GetScene() { return scene_; }
  std::shared_ptr<GameObject> GetParent() { return parent_; }
  std::shared_ptr<Transform> GetTransform() { return transform_; }

 private:
  std::string name_;
  std::shared_ptr<Scene> scene_;
  std::shared_ptr<GameObject> parent_;
  std::shared_ptr<Transform> transform_;
  std::map<std::string, std::shared_ptr<Component>> components_;
};
}  // namespace voodoo

#endif