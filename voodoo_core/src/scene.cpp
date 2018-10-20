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

#include "../include/voodoo/scene.h"
#include "../include/voodoo/game_object.h"
#include "../include/voodoo/logger.h"
#include "../include/voodoo/transform.h"

namespace voodoo {
Scene::Scene() : clear_color_(Color(100, 100, 100)) {}

std::shared_ptr<GameObject> Scene::AddGameObject(std::string name) {
  using namespace std;
  if (GetGameObject(name)) {
    Log::Warning("GameObject with name \"" + name + "\" already exists");
    return nullptr;
  }

  auto go = make_shared<GameObject>(name, shared_from_this());
  game_objects_.insert(pair<string, shared_ptr<GameObject>>(name, go));
  go->AddComponent<Transform>();
  return go;
}

std::shared_ptr<GameObject> Scene::GetGameObject(std::string name) {
  auto go = game_objects_.find(name);
  return go == game_objects_.end() ? nullptr : go->second;
}

std::vector<std::shared_ptr<GameObject>> Scene::GetGameObjects() {
  using namespace std;
  vector<shared_ptr<GameObject>> result;
  for (auto it : game_objects_)
    result.push_back(it.second);
  return result;
}

Color Scene::GetClearColor() { return clear_color_; }
std::shared_ptr<Camera> Scene::GetCamera() { return camera_; }
void Scene::SetCamera(std::shared_ptr<Camera> camera) { camera_ = camera; }
}  // namespace voodoo