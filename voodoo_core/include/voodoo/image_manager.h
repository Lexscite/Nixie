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
// along with Foobar.  If not, see <https://www.gnu.org/licenses/>.

#ifndef VOODOO_IMAGE_MANAGER_H_
#define VOODOO_IMAGE_MANAGER_H_

#include "asset_manager.h"
#include "image.h"

namespace voodoo {
class ImageManager : public AssetManager<Image> {
 public:
  // Temporal singleton
  static ImageManager& Get() {
    static ImageManager instance;
    return instance;
  }

 private:
  virtual std::shared_ptr<Image> Load(std::string filename) override;
};
}  // namespace voodoo

#endif