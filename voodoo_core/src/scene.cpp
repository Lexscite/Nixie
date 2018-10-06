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
  for (auto& game_object : GetGameObjects()) {
    if (!game_object->Init(shared_from_this())) {
      Logger::Write("Failed to initialize actor \"" + game_object->GetName() +
                    "\"");
      return false;
    }
  }

  return true;
}

bool Scene::Update() {
  for (auto& game_object : GetGameObjects()) {
    if (!game_object->Update()) {
      Logger::Write("Failed to update actor \"" + game_object->GetName() +
                    "\"");
      return false;
    }
  }

  return true;
}

bool Scene::AddGameObject(std::shared_ptr<GameObject> new_game_object) {
  std::string name = new_game_object->GetName();

  if (GetGameObject(name) != nullptr) {
    return false;
  }

  game_objects_.insert(std::pair<std::string, std::shared_ptr<GameObject>>(
      name, new_game_object));

  return true;
}

std::shared_ptr<GameObject> Scene::GetGameObject(std::string name) {
  auto result = game_objects_.find(name);

  if (result == game_objects_.end()) {
    return nullptr;
  } else {
    return result->second;
  }
}

std::vector<std::shared_ptr<GameObject>> Scene::GetGameObjects() {
  std::vector<std::shared_ptr<GameObject>> result;

  for (auto& it : game_objects_) {
    result.push_back(it.second);
  }

  return result;
}
}  // namespace voodoo