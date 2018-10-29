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

#include "../include/voodoo/mesh_manager.h"

#include <fstream>

namespace voodoo {
sptr<Mesh> MeshManager::Load(const string& filename) {
  using namespace std;
  ifstream fin;
  fin.open(filename);

  if (fin.fail()) {
    throw runtime_error("Failed to process mesh file: \"" + filename + "\"");
  }

  char input;
  unsigned long v_count;

  fin.get(input);
  while (input != ':') fin.get(input);

  fin >> v_count;

  fin.get(input);
  while (input != ':') fin.get(input);
  fin.get(input);
  fin.get(input);

  vector<vertex_ptn> vertices;
  vertices.resize(v_count);

  for (unsigned int i = 0; i < v_count; i++) {
    fin >> vertices[i].position.x >> vertices[i].position.y >>
        vertices[i].position.z;
    fin >> vertices[i].texture.x >> vertices[i].texture.y;
    fin >> vertices[i].normal.x >> vertices[i].normal.y >> vertices[i].normal.z;
  }

  fin.close();

  return make_shared<Mesh>(vertices);
}
}  // namespace voodoo