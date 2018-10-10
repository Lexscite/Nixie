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

#include "../include/voodoo/directx_manager.h"
#include "../include/voodoo/logger.h"

#include <vector>

namespace voodoo {
DirectXManager::DirectXManager()
    : swap_chain_(nullptr),
      device_(nullptr),
      device_context_(nullptr),
      render_target_view_(nullptr),
      depth_stencil_buffer_(nullptr),
      depth_stencil_state_(nullptr),
      depth_stencil_view_(nullptr),
      rasterizer_state_wireframe_mode_off_(nullptr),
      blend_state_on_(nullptr),
      blend_state_off_(nullptr) {}

DirectXManager* DirectXManager::singleton_;

DirectXManager* DirectXManager::Get() {
  if (singleton_ == 0) singleton_ = new DirectXManager;

  return singleton_;
}

bool DirectXManager::Init(HWND window, unsigned int screen_width,
                          unsigned int screen_height, bool vsync_enabled,
                          bool fullscreen_enabled) {
  HRESULT hr;

  vsync_enabled_ = vsync_enabled;
  fullscreen_enabled_ = fullscreen_enabled;
  msaa_enabled_ = false;
  wireframe_mode_enabled_ = false;
  alpha_blending_enabled_ = true;

  IDXGIFactory* factory;
  hr = CreateDXGIFactory(__uuidof(IDXGIFactory),
                         reinterpret_cast<void**>(&factory));
  if (FAILED(hr)) {
    Logger::Write("Failed to create DXGIFactory");
    return false;
  }

  IDXGIAdapter* adapter;
  hr = factory->EnumAdapters(0, &adapter);
  if (FAILED(hr)) {
    Logger::Write("Failed to enum adapters");
    return false;
  }

  IDXGIOutput* adapter_output;
  hr = adapter->EnumOutputs(0, &adapter_output);
  if (FAILED(hr)) {
    Logger::Write("Failed to enum adapters outputs");
    return false;
  }

  UINT num_modes;
  hr = adapter_output->GetDisplayModeList(
      DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &num_modes, NULL);
  if (FAILED(hr)) {
    Logger::Write("Failed to get display modes list");
    return false;
  }

  DXGI_MODE_DESC* d_modes;
  d_modes = new DXGI_MODE_DESC[num_modes];
  if (!d_modes) {
    Logger::Write("Failed to create display mode list");
    return false;
  }

  hr = adapter_output->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM,
                                          DXGI_ENUM_MODES_INTERLACED,
                                          &num_modes, d_modes);
  if (FAILED(hr)) {
    Logger::Write("Failed to fill display mode list struct");
    return false;
  }

  unsigned int numerator, denominator;
  for (unsigned int i = 0; i < num_modes; i++) {
    if (d_modes[i].Width == static_cast<unsigned int>(screen_width)) {
      if (d_modes[i].Height == static_cast<unsigned int>(screen_height)) {
        numerator = d_modes[i].RefreshRate.Numerator;
        denominator = d_modes[i].RefreshRate.Denominator;
      }
    }
  }

  DXGI_ADAPTER_DESC adapter_desc;
  hr = adapter->GetDesc(&adapter_desc);
  if (FAILED(hr)) {
    Logger::Write("Failed to get adapter description");
    return false;
  }

  adapter_memory_ = static_cast<unsigned int>(
      adapter_desc.DedicatedVideoMemory / 1024 / 1024);

  unsigned int device_creation_flags = 0;
#if defined(_DEBUG)
  device_creation_flags = D3D11_CREATE_DEVICE_DEBUG;
#endif

  std::vector<D3D_DRIVER_TYPE> driver_types = {
      D3D_DRIVER_TYPE_HARDWARE,
      D3D_DRIVER_TYPE_SOFTWARE,
      D3D_DRIVER_TYPE_WARP,
  };

  std::vector<D3D_FEATURE_LEVEL> feature_levels = {
      D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0,
      D3D_FEATURE_LEVEL_9_3,  D3D_FEATURE_LEVEL_9_2,  D3D_FEATURE_LEVEL_9_1};

  for (auto driver_type : driver_types) {
    for (int y = 0; y < feature_levels.size(); y++) {
      hr = D3D11CreateDevice(
          0, driver_type, 0, device_creation_flags, &feature_levels[y],
          static_cast<unsigned int>(feature_levels.size()), D3D11_SDK_VERSION,
          &device_, &feature_level_, &device_context_);

      if (SUCCEEDED(hr)) {
        break;
      }
    }

    if (SUCCEEDED(hr)) {
      break;
    }
  }
  if (FAILED(hr)) {
    Logger::Write("Failed to create DirectX device");
    return false;
  }

  UINT msaa_quality;
  hr = device_->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4,
                                              &msaa_quality);
  if (FAILED(hr)) {
    Logger::Write("Failed to check multisample quality levels");
    return false;
  }

  DXGI_SWAP_CHAIN_DESC swap_chain_desc;
  ZeroMemory(&swap_chain_desc, sizeof(swap_chain_desc));
  swap_chain_desc.OutputWindow = window;
  swap_chain_desc.Windowed = !fullscreen_enabled_;
  swap_chain_desc.BufferDesc.Width = screen_width;
  swap_chain_desc.BufferDesc.Height = screen_height;
  swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  swap_chain_desc.BufferDesc.RefreshRate.Numerator =
      vsync_enabled_ ? numerator : 0;
  swap_chain_desc.BufferDesc.RefreshRate.Denominator =
      vsync_enabled_ ? denominator : 1;
  swap_chain_desc.BufferDesc.ScanlineOrdering =
      DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
  swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
  swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  swap_chain_desc.BufferCount = 1;
  swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
  swap_chain_desc.Flags = 0;
  swap_chain_desc.SampleDesc.Count = msaa_enabled_ ? 4 : 1;
  swap_chain_desc.SampleDesc.Quality = msaa_enabled_ ? msaa_quality - 1 : 0;

  hr = factory->CreateSwapChain(device_, &swap_chain_desc, &swap_chain_);
  if (FAILED(hr)) {
    Logger::Write("Failed to create swap chain");
    return false;
  }

  if (d_modes) {
    delete[] d_modes;
    d_modes = nullptr;
  }

  if (adapter_output) {
    adapter_output->Release();
    adapter_output = nullptr;
  }

  if (adapter) {
    adapter->Release();
    adapter = nullptr;
  }

  if (factory) {
    factory->Release();
    factory = nullptr;
  }

  ID3D11Texture2D* back_buffer;
  hr = swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D),
                              reinterpret_cast<LPVOID*>(&back_buffer));
  if (FAILED(hr)) {
    Logger::Write("Failed to get the back buffer");
    return false;
  }

  hr = device_->CreateRenderTargetView(back_buffer, nullptr,
                                       &render_target_view_);
  if (FAILED(hr)) {
    Logger::Write("Failed to create render target view");
    return false;
  }

  if (back_buffer) {
    back_buffer->Release();
    back_buffer = nullptr;
  }

  D3D11_TEXTURE2D_DESC depth_buffer_desc;
  ZeroMemory(&depth_buffer_desc, sizeof(depth_buffer_desc));
  depth_buffer_desc.Width = screen_width;
  depth_buffer_desc.Height = screen_height;
  depth_buffer_desc.MipLevels = 1;
  depth_buffer_desc.ArraySize = 1;
  depth_buffer_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
  depth_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
  depth_buffer_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
  depth_buffer_desc.CPUAccessFlags = 0;
  depth_buffer_desc.MiscFlags = 0;
  depth_buffer_desc.SampleDesc.Quality = msaa_quality - 1;
  depth_buffer_desc.SampleDesc.Count = msaa_enabled_ ? 4 : 1;
  if (msaa_enabled_) {
    depth_buffer_desc.SampleDesc.Quality = msaa_quality - 1;
  } else {
    depth_buffer_desc.SampleDesc.Quality = 0;
  }

  hr = device_->CreateTexture2D(&depth_buffer_desc, nullptr,
                                &depth_stencil_buffer_);
  if (FAILED(hr)) {
    Logger::Write("Failed to create back buffer texture");
    return false;
  }

  D3D11_DEPTH_STENCIL_DESC depth_stencil_desc;
  ZeroMemory(&depth_stencil_desc, sizeof(depth_stencil_desc));
  depth_stencil_desc.DepthEnable = true;
  depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
  depth_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS;
  depth_stencil_desc.StencilEnable = true;
  depth_stencil_desc.StencilReadMask = 0xFF;
  depth_stencil_desc.StencilWriteMask = 0xFF;
  depth_stencil_desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
  depth_stencil_desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
  depth_stencil_desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
  depth_stencil_desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
  depth_stencil_desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
  depth_stencil_desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
  depth_stencil_desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
  depth_stencil_desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

  hr = device_->CreateDepthStencilState(&depth_stencil_desc,
                                        &depth_stencil_state_);
  if (FAILED(hr)) {
    Logger::Write("Failed to create depth stencil state");
    return false;
  }

  device_context_->OMSetDepthStencilState(depth_stencil_state_, 1);

  D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc;
  ZeroMemory(&depth_stencil_view_desc, sizeof(depth_stencil_view_desc));
  depth_stencil_view_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
  depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
  depth_stencil_view_desc.Texture2D.MipSlice = 0;

  hr = device_->CreateDepthStencilView(
      depth_stencil_buffer_, &depth_stencil_view_desc, &depth_stencil_view_);
  if (FAILED(hr)) {
    Logger::Write("Failed to create depth stencil view");
    return false;
  }

  device_context_->OMSetRenderTargets(1, &render_target_view_,
                                      depth_stencil_view_);

  if (!CreateRasterizerStates()) {
    return false;
  }

  D3D11_VIEWPORT viewport;
  ZeroMemory(&viewport, sizeof(viewport));
  viewport.Width = static_cast<float>(screen_width);
  viewport.Height = static_cast<float>(screen_height);
  viewport.MinDepth = 0;
  viewport.MaxDepth = 1;
  viewport.TopLeftX = 0;
  viewport.TopLeftY = 0;

  device_context_->RSSetViewports(1, &viewport);

  if (!CreateBlendStates()) {
    return false;
  }

  return true;
}

bool DirectXManager::CreateRasterizerStates() {
  HRESULT hr;

  // Wireframe mode
  D3D11_RASTERIZER_DESC rasterizer_desc;
  rasterizer_desc.AntialiasedLineEnable = false;
  rasterizer_desc.CullMode = D3D11_CULL_NONE;
  rasterizer_desc.DepthBias = 0;
  rasterizer_desc.DepthBiasClamp = 0.0f;
  rasterizer_desc.DepthClipEnable = true;
  rasterizer_desc.FrontCounterClockwise = false;
  rasterizer_desc.MultisampleEnable = false;
  rasterizer_desc.ScissorEnable = false;
  rasterizer_desc.SlopeScaledDepthBias = 0.0f;
  rasterizer_desc.FillMode = D3D11_FILL_WIREFRAME;

  hr = device_->CreateRasterizerState(&rasterizer_desc,
                                      &rasterizer_state_wireframe_mode_on_);
  if (FAILED(hr)) {
    return false;
  }

  // Solid mode
  rasterizer_desc.CullMode = D3D11_CULL_BACK;
  rasterizer_desc.FillMode = D3D11_FILL_SOLID;

  hr = device_->CreateRasterizerState(&rasterizer_desc,
                                      &rasterizer_state_wireframe_mode_off_);
  if (FAILED(hr)) {
    return false;
  }

  device_context_->RSSetState(rasterizer_state_wireframe_mode_off_);

  return true;
}

bool DirectXManager::CreateBlendStates() {
  HRESULT hr;

  D3D11_BLEND_DESC blend_desc;
  ZeroMemory(&blend_desc, sizeof(blend_desc));
  blend_desc.RenderTarget[0].BlendEnable = true;
  blend_desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
  blend_desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
  blend_desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
  blend_desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
  blend_desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
  blend_desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
  blend_desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

  hr = device_->CreateBlendState(&blend_desc, &blend_state_on_);
  if (FAILED(hr)) {
    return false;
  }

  blend_desc.RenderTarget[0].BlendEnable = false;

  hr = device_->CreateBlendState(&blend_desc, &blend_state_off_);
  if (FAILED(hr)) {
    return false;
  }

  float factor[4] = {0.0f, 0.0f, 0.0f, 0.0f};
  device_context_->OMSetBlendState(
      alpha_blending_enabled_ ? blend_state_on_ : blend_state_off_, factor,
      0xffffffff);

  return true;
}

void DirectXManager::ToggleWireframeMode() {
  wireframe_mode_enabled_ = !wireframe_mode_enabled_;
  device_context_->RSSetState(wireframe_mode_enabled_
                                  ? rasterizer_state_wireframe_mode_on_
                                  : rasterizer_state_wireframe_mode_off_);
}

void DirectXManager::ToggleBlendMode() {
  alpha_blending_enabled_ = !alpha_blending_enabled_;
  float factor[4] = {0.0f, 0.0f, 0.0f, 0.0f};
  device_context_->OMSetBlendState(
      alpha_blending_enabled_ ? blend_state_on_ : blend_state_off_, factor,
      0xffffffff);
}

void DirectXManager::Release() {
  if (swap_chain_) {
    swap_chain_->SetFullscreenState(false, NULL);
  }

  if (blend_state_on_) {
    blend_state_on_->Release();
    blend_state_on_ = nullptr;
  }

  if (blend_state_off_) {
    blend_state_off_->Release();
    blend_state_off_ = nullptr;
  }

  if (rasterizer_state_wireframe_mode_off_) {
    rasterizer_state_wireframe_mode_off_->Release();
    rasterizer_state_wireframe_mode_off_ = nullptr;
  }

  if (depth_stencil_view_) {
    depth_stencil_view_->Release();
    depth_stencil_view_ = nullptr;
  }

  if (depth_stencil_state_) {
    depth_stencil_state_->Release();
    depth_stencil_state_ = nullptr;
  }

  if (depth_stencil_buffer_) {
    depth_stencil_buffer_->Release();
    depth_stencil_buffer_ = nullptr;
  }

  if (render_target_view_) {
    render_target_view_->Release();
    render_target_view_ = nullptr;
  }

  if (device_context_) {
    device_context_->Release();
    device_context_ = nullptr;
  }

  if (device_) {
    device_->Release();
    device_ = nullptr;
  }

  if (swap_chain_) {
    swap_chain_->Release();
    swap_chain_ = nullptr;
  }
}

void DirectXManager::BeginScene(const Color& c) {
  device_context_->ClearRenderTargetView(render_target_view_, c);
  device_context_->ClearDepthStencilView(depth_stencil_view_, D3D11_CLEAR_DEPTH,
                                         1.0f, 0);
}

void DirectXManager::EndScene() {
  if (vsync_enabled_) {
    swap_chain_->Present(1, 0);
  } else {
    swap_chain_->Present(0, 0);
  }
}

ID3D11Device* DirectXManager::GetDevice() { return device_; }

ID3D11DeviceContext* DirectXManager::GetDeviceContext() {
  return device_context_;
}
}  // namespace voodoo