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

#ifndef VOODOO_SCENE_H_
#define VOODOO_SCENE_H_

#include "color.h"

namespace voodoo {
class GameObject;
class Camera;

class Scene final : public EnableSharedFromThis<Scene> {
 public:
  Scene();

  shared_ptr<Camera> GetCamera();
  void SetCamera(shared_ptr<Camera> camera);

  color GetClearColor();

  shared_ptr<GameObject> AddGameObject(shared_ptr<GameObject> game_object);
  shared_ptr<GameObject> AddGameObject(const string& name);
  shared_ptr<GameObject> GetGameObject(const string& name);
  vector<shared_ptr<GameObject>> GetGameObjects();

 private:
  shared_ptr<GameObject> InsertGameObject(shared_ptr<GameObject>);

 private:
  color clear_color_;
  shared_ptr<Camera> camera_;
  map<string, shared_ptr<GameObject>> game_objects_;
};
}  // namespace voodoo

#endif