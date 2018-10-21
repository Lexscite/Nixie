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

#include "game_object.h"
#include "logger.h"
#include "scene.h"

#include "math.h"

#include <memory>
#include <string>
#include <unordered_map>

namespace voodoo {
class Component : public std::enable_shared_from_this<Component> {
public:
  virtual ~Component() = default;

  std::shared_ptr<Scene> GetScene();
  std::shared_ptr<GameObject> GetGameObject();
  std::shared_ptr<GameObject> GetParent();
  std::shared_ptr<Transform> GetTransform();

  // TODO: find another way
  void SetGameObject(std::shared_ptr<GameObject> go);

  template <class T>
  std::shared_ptr<T> GetComponent() {
    return game_object_->GetComponent<T>();
  }

  template <class T, class... Arg_T>
  std::shared_ptr<T> AddComponent(Arg_T&&... args) {
    using namespace std;
    return game_object_->AddComponent(forward<Arg_T>(args)...);
  }

 protected:
  std::shared_ptr<GameObject> game_object_;
};

// Empty class to store each factory in single registry map
// TODO: Find out a way to get rid of this shoot
class ComponentFactory {};

template <class T>
class IComponentFactory
    : public ComponentFactory,
      public std::enable_shared_from_this<ComponentFactory> {
 public:
  virtual std::shared_ptr<T> Create() = 0;
};

class ComponentFactoryRegistry {
 private:
  using FactoryPtr = std::shared_ptr<ComponentFactory>;
  using FactoryMap = std::unordered_map<std::string, FactoryPtr>;

 public:
  static bool Register(std::string name, FactoryPtr factory) {
    auto it = registry_.find(name);
    if (it == registry_.end()) {
      return false;
    }
    registry_[name] = factory;
    return true;
  }

  template <class T>
  static FactoryPtr Retrieve() {
    auto name = string(typeid(T).name()).erase(0, 14);
    return registry_[name];
  }

 private:
  static FactoryMap registry_;
};
}  // namespace voodoo

// Macro each component should call after it's definition
// in order to register itself in system.
#define VOODOO_REGISTER_COMPONENT(component_name)                              \
  namespace voodoo {                                                           \
  class component_name##Factory : public IComponentFactory<component_name> {   \
    component_name##Factory() {                                                \
      ComponentFactoryRegistry::Register(#component_name, shared_from_this()); \
    }                                                                          \
                                                                               \
    virtual std::shared_ptr<component_name> Create() {                         \
      return std::make_shared<component_name>();                               \
    }                                                                          \
  };                                                                           \
  }

#endif