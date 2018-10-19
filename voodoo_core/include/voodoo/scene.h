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

#include <map>
#include <string>
#include <vector>

namespace voodoo {
class GameObject;
class Camera;

class Scene final : public std::enable_shared_from_this<Scene> {
 public:
  Scene();

  std::shared_ptr<GameObject> AddGameObject(std::string name);
  std::shared_ptr<GameObject> GetGameObject(std::string name);
  std::vector<std::shared_ptr<GameObject>> GetGameObjects();

  Color GetClearColor();
  std::shared_ptr<Camera> GetCamera();
  void SetCamera(std::shared_ptr<Camera> camera);

 private:
  Color clear_color_;
  std::shared_ptr<Camera> camera_;
  std::map<std::string, std::shared_ptr<GameObject>> game_objects_;
};
}  // namespace voodoo

#endif