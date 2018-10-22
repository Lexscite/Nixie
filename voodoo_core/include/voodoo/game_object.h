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

#include "object.h"

namespace voodoo {
class Scene;
class Component;
class Transform;

class GameObject : public Object {
 public:
  GameObject(const string& name, shared_ptr<Scene> scene);

  shared_ptr<GameObject> GetParent();
  void SetParent(shared_ptr<GameObject> parent);

  shared_ptr<Scene> GetScene();
  shared_ptr<Transform> GetTransform();
  vector<shared_ptr<Component>> GetComponents();

  template <class T>
  shared_ptr<T> GetComponent() {
    using namespace std;
    auto name = string(typeid(T).name()).erase(0, 14);
    auto it = components_.find(name);
    bool exists = it != components_.end();
    return exists ? static_pointer_cast<T>(it->second) : nullptr;
  }

  template <class T, class... Types>
  shared_ptr<T> AddComponent(Types&&... args) {
    using namespace std;
    auto name = string(typeid(T).name()).erase(0, 14);
    if (GetComponent<T>()) {
      Log::Warning("GameObject " + GetName() + " already have " + name + " component");
      return nullptr;
    }
    auto component = make_shared<T>(forward<Types>(args)...);
    component->SetGameObject(dynamic_pointer_cast<GameObject>(shared_from_this()));
    components_.insert(pair<string, shared_ptr<Component>>(name, component));
    return component;
  }

 private:
  shared_ptr<Scene> scene_;
  shared_ptr<GameObject> parent_;
  map<string, shared_ptr<Component>> components_;
};
}  // namespace voodoo

#endif