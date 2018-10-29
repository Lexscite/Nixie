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

#ifndef VOODOO_IMAGE_H_
#define VOODOO_IMAGE_H_

namespace voodoo {
struct Image {
 public:
  Image(const int& width, const int& height, const int& channels, byte* data)
      : width(width), height(height), channels(channels), data(data) {}

  ~Image() {
    if (data) {
      delete[] data;
    }
  }

 public:
  int width, height, channels;
  byte* data;
};
}  // namespace voodoo

#endif