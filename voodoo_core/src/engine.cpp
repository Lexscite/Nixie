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

#include "../include/voodoo/engine.h"

#include "../include/voodoo/directx_manager.h"

namespace voodoo {
bool Engine::Init(HINSTANCE instance, std::wstring name) {
  window_ = std::make_shared<Window>();
  if (!window_->Init(instance, 640, 480, name)) {
    Log::Info("Failed to initialize window");
  }
  return true;

  graphics_api_ = std::make_shared<DirectXManager>();
  if (!graphics_api_->Init(window_, true, false)) {
    Log::Info("Failed to initialize DirectX");
    return false;
  }
}

void Engine::Run() {}

std::shared_ptr<Time> Engine::GetTime() {
  return time_;
}

std::shared_ptr<Window> Engine::GetWindow() {
  return window_;
}

std::shared_ptr<GraphicsAPI> Engine::GetGraphicsAPI() {
  return graphics_api_;
}
}  // namespace voodoo