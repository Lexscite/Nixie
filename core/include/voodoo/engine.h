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

#ifndef VOODOO_ENGINE_H_
#define VOODOO_ENGINE_H_

#include "graphics_api.h"
#include "logger.h"
#include "time.h"
#include "window.h"
#include "scene.h"

namespace voodoo {
class Engine {
 public:
  bool Init(HINSTANCE instance, const wstring& name);
  bool LoadScene(sptr<Scene> scene);
  int Run();

  wstring GetName() const;
  sptr<Window> GetWindow() const;
  sptr<GraphicsAPI> GetGraphicsAPI() const;
  sptr<Scene> GetScene() const;

 private:
  void UpdateCaption();
  bool Update();

 private:
  wstring name_;
  sptr<Window> window_;
  sptr<GraphicsAPI> graphics_api_;
  sptr<Scene> scene_;
};
}  // namespace voodoo

#endif