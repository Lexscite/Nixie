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

#ifndef VOODOO_ASSET_MANAGER_H_
#define VOODOO_ASSET_MANAGER_H_

#include "std_mappings.h"

namespace voodoo {
template <class T>
class AssetManager {
 public:
  sptr<T> Retrieve(const string& filename) {
    auto it = resources_.find(filename);
    if (it != resources_.end()) {
      return it->second;
    } else {
      auto resource = Load(filename);
      resources_.insert(pair<string, sptr<T>>(filename, resource));
      return resource;
    }
  }

 protected:
  virtual sptr<T> Load(const string& filename) = 0;

  void Unload(const string& filename) {
    using namespace std;
    auto it = resources_.find(filename);
    if (it == resources_.end()) {
      throw runtime_error("Failed to load resource: \"" + filename + "\"");
    } else {
      resources_.erase(it);
    }
  }

 protected:
  map<string, sptr<T>> resources_;
};
}  // namespace voodoo

#endif