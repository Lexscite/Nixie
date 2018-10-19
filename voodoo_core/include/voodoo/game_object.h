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
  GameObject(std::string name, std::shared_ptr<Scene> scene);

  std::string GetName();
  std::shared_ptr<Scene> GetScene();
  std::shared_ptr<GameObject> GetParent();
  std::shared_ptr<Transform> GetTransform();
  std::vector<std::shared_ptr<Component>> GetComponents();

  template <class T>
  std::shared_ptr<T> GetComponent() {
    using namespace std;
    auto name = string(typeid(T).name()).erase(0, 14);
    auto result = components_.find(name);
    if (result == components_.end()) {
      return nullptr;
    } else {
      return static_pointer_cast<T>(result->second);
    }
  }

  template <class T, class... Arg_T>
  std::shared_ptr<T> AddComponent(Arg_T&&... args) {
    using namespace std;
    auto name = string(typeid(T).name()).erase(0, 14);
    if (GetComponent<T>()) {
      Log::Warning("GameObject " + GetName() + " already have " + name + " component");
      return nullptr;
    }
    auto component = make_shared<T>(forward<Arg_T>(args)...);
    component->SetGameObject(shared_from_this());
    components_.insert(pair<string, shared_ptr<Component>>(name, component));
    return component;
  }

 private:
  std::string name_;
  std::shared_ptr<Scene> scene_;
  std::shared_ptr<GameObject> parent_;
  std::shared_ptr<Transform> transform_;
  std::map<std::string, std::shared_ptr<Component>> components_;
};
}  // namespace voodoo

#endif