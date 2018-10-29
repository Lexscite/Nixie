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

#ifndef VOODOO_OBJECT_H_
#define VOODOO_OBJECT_H_

#include "std_mappings.h"

namespace voodoo {
class Object : public enable_shared_from_this<Object> {
 public:
  Object();
  Object(const string& name);
  Object(const Object& other);
  virtual ~Object() = default;

  uint GetInstanceId() const;
  string GetName() const;

 private:
  static uint GenerateInstanceId();

 protected:
  uint instance_id_;
  string name_;
};
}  // namespace voodoo

#endif  // VOODOO_OBJECT_H_