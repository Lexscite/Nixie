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
bool Engine::Init(HINSTANCE instance, std::wstring name) {
  name_ = name;

  time_ = std::make_shared<Time>();

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

void Engine::Release() {
  if (graphics_api_) {
    graphics_api_->Release();
    graphics_api_ = nullptr;
  }
}

int Engine::Run() {
  MSG msg;
  memset(&msg, 0, sizeof(msg));
  while (msg.message != WM_QUIT) {
    if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    } else {
      time_->Tick();
      UpdateCaption();
      if(!Update()) {
        return false;
      }
      graphics_api_->Render(scene_);
    }
  }

  return static_cast<int>(msg.wParam);
}

bool Engine::Update() {
  using namespace std;

  for (auto go : scene_->GetGameObjects()) {
    for (auto c : go->GetComponents()) {
      auto b = dynamic_pointer_cast<Behavior>(c);
      if (b) {
        if (!b->Tick()) {
          Log::Error("Failed to update behavior");
          return false;
        }
      }
    }
  }

  return true;
}

void Engine::UpdateCaption() {
  using namespace std;
  static int frame_count = 0;
  static float time_elapsed = 0;

  frame_count++;

  if ((time_->GetTime() - time_elapsed) >= 1) {
    float fps = static_cast<float>(frame_count);
    float ms_per_frame = 1000 / fps;

    wostringstream caption;
    caption.precision(6);
    caption << name_ << " | FPS: " << fps << " Frame time: " << ms_per_frame << "ms";
    SetWindowText(window_->GetHandle(), caption.str().c_str());

    frame_count = 0;
    time_elapsed++;
  }
}

bool Engine::LoadScene(std::shared_ptr<Scene> scene) {
  using namespace std;
  scene_ = scene;
  vector<std::shared_ptr<Renderer>> renderers;

  for (auto go : scene_->GetGameObjects()) {
    auto r = go->GetComponent<Renderer>();
    if (r) renderers.push_back(r);
    for (auto c : go->GetComponents()) {
      auto b = dynamic_pointer_cast<Behavior>(c);
      if (b) {
        if (!b->Init()) {
          Log::Error("Failed to init object");
          return false;
        }
      }
    }
  }

  for (auto r : renderers) {
    graphics_api_->CreateMeshBuffers(r->GetMesh());
  }

  return true;
}

std::wstring Engine::GetName() { return name_; }
std::shared_ptr<Time> Engine::GetTime() { return time_; }
std::shared_ptr<Window> Engine::GetWindow() { return window_; }
std::shared_ptr<GraphicsAPI> Engine::GetGraphicsAPI() { return graphics_api_; }
std::shared_ptr<Scene> Engine::GetScene() { return scene_; }
}  // namespace voodoo