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

#include <map>
#include <string>

namespace voodoo {
template <class T>
class AssetManager {
 public:
  std::shared_ptr<T> Retrieve(std::string filename) {
    auto it = resources_.find(filename);

    if (it != resources_.end()) {
      return it->second;
    } else {
      auto resource = Load(filename);
      resources_.insert(
          std::pair<std::string, std::shared_ptr<T>>(filename, resource));
      return resource;
    }
  }

 protected:
  virtual std::shared_ptr<T> Load(std::string) = 0;

  void Unload(std::string filename) {
    auto it = resources_.find(filename);

    if (it == resources_.end()) {
      throw std::runtime_error("Trying to unload non-existing resource: \"" +
                               filename + "\"");
    } else {
      resources_.erase(it);
    }
  }

 protected:
  std::map<std::string, std::shared_ptr<T>> resources_;
};
}  // namespace voodoo

#endif