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
Scene::Scene() : clear_color_(color(100, 100, 100)) {}

shared_ptr<Camera> Scene::GetCamera() {
  return camera_;
}

void Scene::SetCamera(shared_ptr<Camera> camera) {
  camera_ = camera;
}

color Scene::GetClearColor() {
  return clear_color_;
}

std::shared_ptr<GameObject> Scene::AddGameObject(const string& name) {
  using namespace std;
  if (GetGameObject(name)) {
    Log::Warning("GameObject with name \"" + name + "\" already exists");
    return nullptr;
  }

  auto game_object = make_shared<GameObject>(name, shared_from_this());
  game_objects_.insert(pair<string, shared_ptr<GameObject>>(name, game_object));
  game_object->AddComponent<Transform>();

  return game_object;
}

std::shared_ptr<GameObject> Scene::GetGameObject(const string& name) {
  auto it = game_objects_.find(name);
  return it != game_objects_.end() ? it->second : nullptr;
}

std::vector<std::shared_ptr<GameObject>> Scene::GetGameObjects() {
  vector<shared_ptr<GameObject>> game_objects;
  for (auto it : game_objects_)
    game_objects.push_back(it.second);

  return game_objects;
}
}  // namespace voodoo