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

template <class T>
using enable_if_component_t = enable_if_t<is_base_of_v<Component, T>, int>;

template<class T>
string get_class_name() {
  return string(typeid(T).name()).erase(0, 14);
}

class GameObject final : public Object {
 public:
  GameObject() = delete;
  GameObject(const string& name, sptr<Scene> scene);

  // No copy
  GameObject(const GameObject& other) = delete;
  GameObject& operator=(const GameObject& other) = delete;

  void Enable();
  void Disable();
  bool IsActive();

  sptr<GameObject> GetParent() const;
  void SetParent(sptr<GameObject> parent);

  sptr<Scene> GetScene() const;
  sptr<Transform> GetTransform() const;
  vector<sptr<Component>> GetComponents() const;
  sptr<Component> AddComponent(sptr<Component> component);

  template <class T, enable_if_component_t<T> = 0>
  sptr<T> GetComponent() const {
    auto name = get_class_name<T>();
    auto component = GetComponentByName(name);
    return component ? s_cast<T>(component) : nullptr;
  }

  template <class T, class... Types, enable_if_component_t<T> = 0>
  sptr<T> AddComponent(Types&&... args);

 private:
   sptr<Component> GetComponentByName(const string& name) const;
   sptr<Component> InsertComponent(sptr<Component> component);

 private:
  sptr<Scene> scene_;
  sptr<GameObject> parent_;
  map<string, sptr<Component>> components_;

  bool active_;
};
}  // namespace voodoo

#endif