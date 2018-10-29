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

#ifndef VOODOO_MEMORY_H_
#define VOODOO_MEMORY_H_

#include "std_mappings.h"

namespace voodoo {
class Releasable {
 public:
  virtual ~Releasable() = default;
  virtual void Release() = 0;
};

template <class T>
using enable_if_releasable_t = enable_if_t<is_base_of_v<Releasable, T>, int>;

template <class T>
void safe_release(T p) {
  if (p) {
    p->Release();
    p = nullptr;
  }
}
}  // namespace voodoo

#endif  // VOODOO_MEMORY_H_