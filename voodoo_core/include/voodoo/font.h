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

#ifndef VOODOO_FONT_H_
#define VOODOO_FONT_H_

#include "mesh.h"
#include "texture.h"
#include "vector.h"

#include <map>

namespace voodoo {
class Font {
 public:
  struct CharData {
    float x, y, width, height, origin_x, origin_y;
  };

 public:
  Font();

  bool Init();

  float GetWidth();
  float GetHeight();
  CharData GetCharData(const char& c);

 private:
  float width_, height_;

  std::map<char, Font::CharData> characters_;
};
}  // namespace voodoo

#endif