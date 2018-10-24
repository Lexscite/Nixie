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

class Scene final : public enable_shared_from_this<Scene> {
 public:
  Scene();

  sptr<Camera> GetCamera();
  void SetCamera(sptr<Camera> camera);

  color GetClearColor();

  sptr<GameObject> AddGameObject(sptr<GameObject> game_object);
  sptr<GameObject> AddGameObject(const string& name);
  sptr<GameObject> GetGameObject(const string& name);

  vector<sptr<GameObject>> GetGameObjects() const;

 private:
  sptr<GameObject> InsertGameObject(sptr<GameObject> game_object);

 private:
  color clear_color_;
  sptr<Camera> camera_;
  map<string, sptr<GameObject>> game_objects_;
};
}  // namespace voodoo

#endif