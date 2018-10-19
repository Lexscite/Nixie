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

#ifndef VOODOO_DIRECTX_MANAGER_H_
#define VOODOO_DIRECTX_MANAGER_H_

#include "color.h"
#include "graphics_api.h"
#include "window.h"

#ifdef _WIN32
// Enable DirectX
#define VOODOO_DIRECTX
#include <windows.h>
#endif  // _WIN32

#ifdef VOODOO_DIRECTX
// Core DirectX dependencies
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#include <d3d11.h>
#endif  // VOODOO_DIRECTX

namespace voodoo {
class DirectX : public GraphicsAPI {
 public:
  DirectX();
  virtual bool Init(std::shared_ptr<Window> window) override;
  virtual bool Render(std::shared_ptr<Renderer> renderer,
                      std::shared_ptr<Camera> camera) override;

  void Release();
  void BeginScene(const Color& c);
  void EndScene();

  void ToggleWireframeMode();
  void ToggleBlendMode();

  std::shared_ptr<ID3D11Device> GetDevice();
  std::shared_ptr<ID3D11DeviceContext> GetDeviceContext();

 private:
  bool CreateDevice();
  bool CreateSwapChain(std::shared_ptr<Window> window);
  bool CreateRenderTargetView();
  bool CreateDepthBuffer(std::shared_ptr<Window> window);
  bool CreateDepthStencilView();
  bool CreateDepthStencilStates();
  bool CreateRasterizerStates();
  bool CreateBlendStates();
  bool CreateViewport(std::shared_ptr<Window> window);

 private:
  bool vsync_enabled_;
  bool fullscreen_enabled_;
  bool wireframe_mode_enabled_;
  bool alpha_blending_enabled_;
  bool msaa_enabled_;
  unsigned int msaa_quality_;
  unsigned int adapter_memory_;
  char adapter_desc_[128];

  std::shared_ptr<ID3D11Device> device_;
  std::shared_ptr<ID3D11DeviceContext> device_context_;

  D3D_FEATURE_LEVEL feature_level_;
  IDXGISwapChain* swap_chain_;

  ID3D11RenderTargetView* render_target_view_;
  ID3D11Texture2D* depth_stencil_buffer_;
  ID3D11DepthStencilState* depth_stencil_state_;
  ID3D11DepthStencilView* depth_stencil_view_;
  ID3D11RasterizerState* rasterizer_state_wireframe_mode_on_;
  ID3D11RasterizerState* rasterizer_state_wireframe_mode_off_;
  ID3D11BlendState* blend_state_on_;
  ID3D11BlendState* blend_state_off_;
};
}  // namespace voodoo

#endif