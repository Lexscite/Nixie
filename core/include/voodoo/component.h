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

#ifndef VOODOO_COMPONENT_H_
#define VOODOO_COMPONENT_H_

#include "object.h"

#include "game_object.h"
#include "logger.h"
#include "scene.h"

#include "math.h"

namespace voodoo {
class Component : public Object {
 public:
  virtual ~Component() = default;

  sptr<GameObject> GetGameObject();
  void SetGameObject(sptr<GameObject> game_object);

  sptr<GameObject> GetParent();
  void SetParent(sptr<GameObject> parent);

  sptr<Scene> GetScene();
  sptr<Transform> GetTransform();
  sptr<Component> AddComponent(sptr<Component> component);

  template <class T, enable_if_component_t<T> = 0>
  sptr<T> GetComponent() {
    return game_object_->GetComponent<T>();
  }

  template <class T, class... Types, enable_if_component_t<T> = 0>
  sptr<T> AddComponent(Types&&... args) {
    using namespace std;
    return game_object_->AddComponent(forward<Types>(args)...);
  }

  template <class T, class... Types, enable_if_component_t<T> = 0>
  static sptr<T> Create(Types&&... args) {
    using namespace std;
    auto component = make_shared<T>(forward<Types>(args)...);
    auto name = get_class_name<T>();
    component->SetName(name);
    return component;
  }

 protected:
  Component() = default;

 private:
  void SetName(string name);

 protected:
  sptr<GameObject> game_object_;
};

// Defined here to avoid circular dependency
template <class T, class... Types, enable_if_component_t<T>>
sptr<T> GameObject::AddComponent(Types&&... args) {
  using namespace std;
  auto name = get_class_name<T>();
  if (GetComponentByName(name)) {
    Log::Warning("GameObject " + GetName() + " already have " + name + " component");
    return nullptr;
  }
  auto component = Component::Create<T>(forward<Types>(args)...);
  return d_cast<T>(InsertComponent(component));
}
}  // namespace voodoo
#endif  // VOODOO_COMPONENT_H_