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

#ifndef VOODOO_MESH_CONVERTER_H_
#define VOODOO_MESH_CONVERTER_H_

#include <voodoo/math.h>

namespace voodoo {
struct Face {
  vec3<int> v;
  vec3<int> t;
  vec3<int> n;
};

class ModelConverter final {
 public:
  static ModelConverter* Get();

  bool Init();
  bool Run();

 private:
  ModelConverter() = default;

  bool CheckFile(char* filename);
  bool ProcessFile(char* filename);

  bool GetModelMetrics(char* filename);
  bool Read(char* filename);
  bool Write(char* filename);

 private:
  static ModelConverter* singleton_;

  int v_count_, t_count_, n_count_, f_count_;

  std::vector<vec3<float>> v_coords_;
  std::vector<vec3<float>> t_coords_;
  std::vector<vec3<float>> n_coords_;
  std::vector<Face> faces_;
};
}  // namespace voodoo

#endif