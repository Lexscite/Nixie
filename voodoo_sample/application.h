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

#ifndef VOODOO_APPLICATION_H_
#define VOODOO_APPLICATION_H_

#include "connection.h"

#include <voodoo/directx_manager.h>
#include <voodoo/scene.h>
#include <voodoo/time.h>
#include <voodoo/window.h>

namespace voodoo {
class Application final {
 public:
  static bool Init(HINSTANCE instance, std::wstring name);
  static int Run();

  static std::shared_ptr<DirectXManager> GetDirectX();
  static std::shared_ptr<Scene> GetScene();

 private:
  static bool Update(float delta_time);
  static void CalculateFrameStats();
  static bool LoadScene();

 private:
  static std::wstring name_;
  static std::shared_ptr<Window> window_;
  static Time* time_;
  static std::shared_ptr<DirectXManager> directx_;
  static std::shared_ptr<Scene> scene_;
};
}  // namespace voodoo

#endif