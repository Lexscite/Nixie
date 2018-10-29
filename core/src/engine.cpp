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

#include "../include/voodoo/engine.h"

#include "../include/voodoo/behavior.h"
#include "../include/voodoo/directx.h"
#include "../include/voodoo/logger.h"
#include "../include/voodoo/renderer.h"

#include <sstream>

namespace voodoo {
bool Engine::Init(HINSTANCE instance, const wstring& name) {
  name_ = name;

  window_ = std::make_shared<Window>();
  if (!window_->Init(instance, 640, 480, name)) {
    Log::Error("Failed to initialize window");
    return false;
  }

  graphics_api_ = std::make_shared<DirectX>();
  if (!graphics_api_->Init(window_)) {
    Log::Error("Failed to initialize DirectX");
    return false;
  }

  return true;
}

bool Engine::LoadScene(sptr<Scene> scene) {
  scene_ = scene;
  vector<sptr<Renderer>> renderers;
  for (auto& game_object : scene_->GetGameObjects()) {
    if (auto renderer = game_object->GetComponent<Renderer>()) {
      renderers.push_back(renderer);
    }
    for (auto& component : game_object->GetComponents()) {
      if (auto behavior = d_cast<Behavior>(component)) {
        if (!behavior->Init()) {
          Log::Error("Failed to init object");
          return false;
        }
      }
    }
  }

  for (auto& renderer : renderers) {
    graphics_api_->CreateMeshBuffers(renderer->GetMesh());
  }

  return true;
}

int Engine::Run() {
  MSG msg;
  memset(&msg, 0, sizeof(msg));
  while (msg.message != WM_QUIT) {
    if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    } else {
      Time::Tick();
      UpdateCaption();
      if (!Update()) return false;
      graphics_api_->Render(scene_);
    }
  }

  return static_cast<int>(msg.wParam);
}

void Engine::UpdateCaption() {
  static float fps;
  static float time;

  if ((Time::GetTime() - time) >= 1) {
    wostringstream caption;
    caption.precision(6);
    caption << name_ << " | FPS: " << fps << " (" << 1000 / fps << "ms)";
    SetWindowText(window_->GetHandle(), caption.str().c_str());
    fps = 0;
    time = Time::GetTime();
  } else {
    fps++;
  }
}

bool Engine::Update() {
  for (auto& game_object : scene_->GetGameObjects()) {
    if (game_object->IsActive()) {
      for (auto& component : game_object->GetComponents()) {
        if (auto behavior = d_cast<Behavior>(component)) {
          if (!behavior->Tick()) {
            Log::Error("Failed to update behavior");
            return false;
          }
        }
      }
    }
  }

  return true;
}

wstring Engine::GetName() const { return name_; }

sptr<Window> Engine::GetWindow() const { return window_; }

sptr<GraphicsAPI> Engine::GetGraphicsAPI() const { return graphics_api_; }

sptr<Scene> Engine::GetScene() const { return scene_; }
}  // namespace voodoo