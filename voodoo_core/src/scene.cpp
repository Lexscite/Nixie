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

sptr<Camera> Scene::GetCamera() {
  return camera_;
}

void Scene::SetCamera(sptr<Camera> camera) {
  camera_ = camera;
}

color Scene::GetClearColor() {
  return clear_color_;
}

sptr<GameObject> Scene::AddGameObject(sptr<GameObject> game_object) {
  auto name = game_object->GetName();
  if (!GetGameObject(name)) {
    Log::Warning("GameObject with name \"" + name + "\" already exists");
    return nullptr;
  }

  return InsertGameObject(game_object);
}

sptr<GameObject> Scene::AddGameObject(const string& name) {
  using namespace std;
  if (GetGameObject(name)) {
    Log::Warning("GameObject with name \"" + name + "\" already exists");
    return nullptr;
  }

  auto game_object = make_shared<GameObject>(name, shared_from_this());
  game_object->AddComponent<Transform>();
  return InsertGameObject(game_object);
}

sptr<GameObject> Scene::GetGameObject(const string& name) {
  auto it = game_objects_.find(name);
  return it != game_objects_.end() ? it->second : nullptr;
}

vector<sptr<GameObject>> Scene::GetGameObjects() const {
  vector<sptr<GameObject>> game_objects;
  for (auto& it : game_objects_)
    game_objects.push_back(it.second);
  return game_objects;
}

sptr<GameObject> Scene::InsertGameObject(sptr<GameObject> game_object) {
  auto name = game_object->GetName();
  game_objects_.insert(pair<string, sptr<GameObject>>(name, game_object));
  return game_object;
}
}  // namespace voodoo