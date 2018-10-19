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

#ifndef VOODOO_WINDOW_H_
#define VOODOO_WINDOW_H_

#include "rect.h"

#ifdef _WIN32
#include <windows.h>
#endif  // _WIN32

#include <string>

namespace voodoo {
class Window {
 public:
  bool Init(HINSTANCE instance, int width, int height, std::wstring caption);
  HWND GetHandle();
  Rect<int> GetRect();
  int GetWidth();
  int GetHeight();

 private:
  LRESULT CALLBACK MsgProc(HWND handle, UINT msg,
                           WPARAM w_param, LPARAM l_param);
  static LRESULT CALLBACK MsgRouter(HWND handle, UINT msg,
                                    WPARAM w_param, LPARAM l_param);

 private:
  HWND handle_;
};
}  // namespace voodoo

#endif  // VOODOO_WINDOW_H_