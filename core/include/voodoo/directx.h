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

namespace voodoo {
class DirectX : public GraphicsAPI {
 public:
  DirectX();

  virtual bool Init(std::shared_ptr<Window> window) override;
  virtual bool Render(std::shared_ptr<Scene>) override;
  virtual bool CreateMeshBuffers(std::shared_ptr<Mesh> mesh) override;
  virtual void Release() override;

  void ToggleWireframeMode();
  void ToggleBlendMode();

 private:
  void BeginScene(const color& clear_color);
  void EndScene();

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

  D3D_FEATURE_LEVEL feature_level_;
  IDXGISwapChain* swap_chain_;

  ID3D11RenderTargetView* rt_view_;

  ID3D11Texture2D* ds_buffer_;
  ID3D11DepthStencilView* ds_view_;

  ID3D11DepthStencilState* dss_default_;

  ID3D11RasterizerState* rs_default_;
  ID3D11RasterizerState* rs_wireframe_;

  ID3D11BlendState* bs_default_;
  ID3D11BlendState* bs_no_blend_;
};
}  // namespace voodoo

#endif