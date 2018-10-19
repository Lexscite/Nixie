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
// along with Foobar.  If not, see <https://www.gnu.org/licenses/>.

#include "../include/voodoo/scene.h"
#include "../include/voodoo/game_object.h"
#include "../include/voodoo/logger.h"
#include "../include/voodoo/transform.h"

namespace voodoo {
Scene::Scene() : clear_color_(Color(100, 100, 100)) {}

bool Scene::Init() {
  for (auto go : GetGameObjects()) {
    if (!go->Init(shared_from_this())) {
      Log::Info("Failed to initialize actor \"" + go->GetName() + "\"");
      return false;
    }
  }

  return true;
}

bool Scene::Update() {
  for (auto go : GetGameObjects()) {
    if (!go->Update()) {
      Log::Error("Failed to update game object \"" + go->GetName() + "\"");
      return false;
    }
  }

  return true;
}

bool Scene::AddGameObject(std::shared_ptr<GameObject> go) {
  using namespace std;
  string name = go->GetName();

  if (GetGameObject(name)) {
    Log::Error("Failed to add game object \"" + name + "\"");
    return false;
  }

  game_objects_.insert(pair<string, shared_ptr<GameObject>>(name, go));
  return true;
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
}  // namespace voodoo