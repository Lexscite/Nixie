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

#include "../include/voodoo/object.h"

namespace voodoo {
Object::Object()
    : instance_id_(GenerateInstanceId()),
      name_() {}

Object::Object(const string& name) : Object() {
  name_ = name;
}

Object::Object(const Object& other) : Object(other.name_) {}

uint Object::GetInstanceId() const {
  return instance_id_;
}

string Object::GetName() const {
  return name_;
}

uint Object::GenerateInstanceId() {
  static uint instance_id_counter;
  uint instance_id = instance_id_counter;
  instance_id_counter++;
  return instance_id;
}
}  // namespace voodoo