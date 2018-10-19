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

#ifndef VOODOO_COMPONENT_FACTORY_H_
#define VOODOO_COMPONENT_FACTORY_H_

#include "component.h"

#include <unordered_map>

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

namespace voodoo {
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
 public:
  static bool Register(std::string factory_name,
                       std::shared_ptr<ComponentFactory> factory) {
    auto it = registry_.find(factory_name);

    if (it == registry_.end()) {
      return false;
    }

    registry_[factory_name] = factory;

    return true;
  }

 private:
  static std::unordered_map<std::string, std::shared_ptr<ComponentFactory>>
      registry_;
};
}  // namespace voodoo

#endif