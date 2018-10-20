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

#include "../include/voodoo/window.h"

namespace voodoo {
bool Window::Init(HINSTANCE instance,
                  int width, int height,
                  std::wstring caption) {
  WNDCLASSEX wcex;
  std::wstring wc_name = caption + L"Window";
  DWORD style = WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU;
  DWORD ex_style = WS_EX_APPWINDOW;

  memset(&wcex, 0, sizeof(wcex));
  wcex.cbClsExtra = NULL;
  wcex.cbWndExtra = NULL;
  wcex.cbSize = sizeof(wcex);
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.hInstance = instance;
  wcex.lpfnWndProc = MsgRouter;
  wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
  wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
  wcex.lpszMenuName = caption.c_str();
  wcex.lpszClassName = wc_name.c_str();
  if (!RegisterClassEx(&wcex)) {
    return false;
  }

  handle_ = CreateWindowEx(
      ex_style,
      wc_name.c_str(),
      caption.c_str(),
      style,
      0, 0, width, height,
      NULL, NULL, instance, NULL);
  if (!handle_) {
    return false;
  }

  // Adjust window position and size
  int x = GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2;
  int y = GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2;
  RECT wr = {x, y, x + width, y + height};
  AdjustWindowRectEx(&wr, style, false, ex_style);
  SetWindowPos(handle_, NULL,
               wr.left, wr.top,
               wr.right - wr.left, wr.bottom - wr.top,
               NULL);

  ShowWindow(handle_, SW_SHOW);

  return true;
}

HWND Window::GetHandle() { return handle_; }

Rect<int> Window::GetRect() {
  RECT r;
  GetClientRect(handle_, &r);
  return Rect<int>(static_cast<int>(r.left), static_cast<int>(r.top),
                   static_cast<int>(r.right - r.left),
                   static_cast<int>(r.bottom - r.top));
}

int Window::GetWidth() { return GetRect().size.x; }

int Window::GetHeight() { return GetRect().size.y; }

LRESULT CALLBACK Window::MsgProc(HWND handle, UINT msg, WPARAM w_param,
                                 LPARAM l_param) {
  switch (msg) {
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
    case WM_MOVE:
      if (LOWORD(w_param) == WM_MOVING) {
      } else {
      }
      return 0;
    case WM_MENUCHAR:
      return MAKELRESULT(0, MNC_CLOSE);
    case WM_GETMINMAXINFO:
      ((MINMAXINFO*)l_param)->ptMinTrackSize.x = 200;
      ((MINMAXINFO*)l_param)->ptMinTrackSize.y = 200;
      return 0;
    case WM_ACTIVATEAPP:
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
    case WM_KEYUP:
    case WM_SYSKEYUP:
    default:
      return DefWindowProc(handle, msg, w_param, l_param);
  }
}

LRESULT CALLBACK Window::MsgRouter(HWND handle, UINT msg, WPARAM w_param,
                                   LPARAM l_param) {
  if (msg == WM_NCCREATE) {
    SetWindowLongPtr(handle, GWLP_USERDATA,
                     (LONG_PTR)((CREATESTRUCT*)l_param)->lpCreateParams);
    return TRUE;
  }

  return ((Window*)GetWindowLongPtr(handle, GWLP_USERDATA))
      ->MsgProc(handle, msg, w_param, l_param);
}
}  // namespace voodoo