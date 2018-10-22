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

#include "../include/voodoo/directx.h"

#include "../include/voodoo/logger.h"

// Components
#include "../include/voodoo/camera.h"
#include "../include/voodoo/renderer.h"
#include "../include/voodoo/transform.h"

namespace voodoo {
DirectX::DirectX()
    : swap_chain_(nullptr),
      render_target_view_(nullptr),
      depth_stencil_buffer_(nullptr),
      depth_stencil_state_(nullptr),
      depth_stencil_view_(nullptr),
      rasterizer_state_wireframe_mode_off_(nullptr),
      blend_state_on_(nullptr),
      blend_state_off_(nullptr) {}

bool DirectX::Init(std::shared_ptr<Window> window) {
  vsync_enabled_ = true;
  fullscreen_enabled_ = false;
  msaa_enabled_ = false;
  wireframe_mode_enabled_ = false;
  alpha_blending_enabled_ = true;

  if (!CreateDevice()) {
    Log::Error("Failed to create device");
    return false;
  }

  if (!CreateSwapChain(window)) {
    Log::Error("Failed to create swap chain");
    return false;
  }

  if (!CreateRenderTargetView()) {
    Log::Error("Failed to create render target view");
    return false;
  }

  if (!CreateDepthBuffer(window)) {
    Log::Error("Failed to create depth buffer");
    return false;
  }

  if (!CreateDepthStencilView()) {
    Log::Error("Failed to create depth stencil view");
    return false;
  }

  if (!CreateDepthStencilStates()) {
    Log::Error("Failed to create depth stencil states");
    return false;
  }

  if (!CreateRasterizerStates()) {
    Log::Error("Failed to create rasterizer states");
    return false;
  }

  if (!CreateBlendStates()) {
    Log::Error("Failed to create blend states");
    return false;
  }

  if (!CreateViewport(window)) {
    Log::Error("Failed to create viewport");
    return false;
  }

  device_context_->OMSetDepthStencilState(depth_stencil_state_, 1);
  device_context_->OMSetRenderTargets(
      1, &render_target_view_, depth_stencil_view_);

  return true;
}

bool DirectX::Render(std::shared_ptr<Scene> scene) {
  using namespace std;
  vector<shared_ptr<Renderer>> renderers;
  auto camera = scene->GetCamera();

  BeginScene(scene->GetClearColor());

  for (auto go : scene->GetGameObjects()) {
    auto r = go->GetComponent<Renderer>();
    if (r) renderers.push_back(r);
  }

  for (auto renderer : renderers) {
    auto wm = renderer->GetTransform()->GetWorldMatrix();
    auto vm = camera->GetViewMatrix();
    auto pm = camera->GetProjectionMatrix();

    auto material = renderer->GetMaterial();
    auto mesh = renderer->GetMesh();
    auto shader = material->shader;
    auto srv = material->texture->srv;
    auto buffers = mesh_buffers_[mesh];
    auto v_buffer = buffers.first;
    auto i_buffer = buffers.second;

    if (!shader->Update(wm, vm, pm, srv)) {
      throw std::runtime_error("Failed to update shader");
    }

    unsigned int stride = sizeof(mesh->vertices[0]);
    unsigned int offset = 0;

    device_context_->IASetVertexBuffers(0, 1, &v_buffer, &stride, &offset);
    device_context_->IASetIndexBuffer(i_buffer, DXGI_FORMAT_R32_UINT, 0);
    device_context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    device_context_->DrawIndexed(mesh->index_count, 0, 0);
  }

  EndScene();

  return true;
}

bool DirectX::CreateMeshBuffers(std::shared_ptr<Mesh> mesh) {
  HRESULT hr;

  D3D11_BUFFER_DESC desc;
  desc.Usage = D3D11_USAGE_DEFAULT;
  desc.ByteWidth = sizeof(mesh->vertices[0]) * mesh->vertex_count;
  desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  desc.CPUAccessFlags = 0;
  desc.MiscFlags = 0;
  desc.StructureByteStride = 0;

  D3D11_SUBRESOURCE_DATA data;
  data.pSysMem = mesh->vertices.data();
  data.SysMemPitch = 0;
  data.SysMemSlicePitch = 0;

  ID3D11Buffer* v;
  hr = device_->CreateBuffer(&desc, &data, &v);
  if (FAILED(hr)) {
    return false;
  }

  desc.ByteWidth = sizeof(mesh->indices[0]) * mesh->index_count;
  desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

  data.pSysMem = mesh->indices.data();

  ID3D11Buffer* i;
  hr = device_->CreateBuffer(&desc, &data, &i);
  if (FAILED(hr)) {
    return false;
  }

  auto v_buffer = MeshBufferPtr(v);
  auto i_buffer = MeshBufferPtr(i);
  auto buffers = MeshBufferPair(v, i);

  mesh_buffers_.insert(std::pair<std::shared_ptr<Mesh>,
                                 MeshBufferPair>(mesh, buffers));

  return true;
}

void DirectX::Release() {
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

  device_context_->Release();
  device_->Release();

  if (swap_chain_) {
    swap_chain_->Release();
    swap_chain_ = nullptr;
  }
}

void DirectX::ToggleWireframeMode() {
  wireframe_mode_enabled_ = !wireframe_mode_enabled_;
  device_context_->RSSetState(wireframe_mode_enabled_
                                  ? rasterizer_state_wireframe_mode_on_
                                  : rasterizer_state_wireframe_mode_off_);
}

void DirectX::ToggleBlendMode() {
  alpha_blending_enabled_ = !alpha_blending_enabled_;
  float factor[4] = {0.0f, 0.0f, 0.0f, 0.0f};
  device_context_->OMSetBlendState(alpha_blending_enabled_
                                       ? blend_state_on_
                                       : blend_state_off_,
                                   factor, 0xffffffff);
}

void DirectX::BeginScene(const color& c) {
  device_context_->ClearRenderTargetView(render_target_view_, c);
  device_context_->ClearDepthStencilView(depth_stencil_view_, D3D11_CLEAR_DEPTH,
                                         1.0f, 0);
}

void DirectX::EndScene() {
  if (vsync_enabled_) {
    swap_chain_->Present(1, 0);
  } else {
    swap_chain_->Present(0, 0);
  }
}

bool DirectX::CreateDevice() {
  HRESULT hr;

  unsigned int device_creation_flags = 0;
#ifdef _DEBUG
  device_creation_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif  // _DEBUG

  std::vector<D3D_DRIVER_TYPE> driver_types = {
      D3D_DRIVER_TYPE_HARDWARE,
      D3D_DRIVER_TYPE_SOFTWARE,
      D3D_DRIVER_TYPE_WARP,
  };

  std::vector<D3D_FEATURE_LEVEL> feature_levels = {
      D3D_FEATURE_LEVEL_11_0,
      D3D_FEATURE_LEVEL_10_1,
      D3D_FEATURE_LEVEL_10_0,
      D3D_FEATURE_LEVEL_9_3,
      D3D_FEATURE_LEVEL_9_2,
      D3D_FEATURE_LEVEL_9_1,
  };

  ID3D11Device* device = nullptr;
  ID3D11DeviceContext* device_context = nullptr;
  for (auto driver_type : driver_types) {
    for (int y = 0; y < feature_levels.size(); y++) {
      hr = D3D11CreateDevice(
          0, driver_type, 0, device_creation_flags, &feature_levels[y],
          static_cast<unsigned int>(feature_levels.size()), D3D11_SDK_VERSION,
          &device, &feature_level_, &device_context);

      if (SUCCEEDED(hr)) {
        device_ = std::shared_ptr<ID3D11Device>(device);
        device_context_ = std::shared_ptr<ID3D11DeviceContext>(device_context);
        return true;
      }
    }
  }

  if (FAILED(hr)) {
    Log::Info("Failed to create DirectX device");
    delete device;
    delete device_context;
    return false;
  }

  return true;
}

bool DirectX::CreateSwapChain(std::shared_ptr<Window> window) {
  HRESULT hr;

  IDXGIFactory* factory;
  hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&factory));
  if (FAILED(hr)) {
    return false;
  }

  IDXGIAdapter* adapter;
  hr = factory->EnumAdapters(0, &adapter);
  if (FAILED(hr)) {
    return false;
  }

  IDXGIOutput* adapter_output;
  hr = adapter->EnumOutputs(0, &adapter_output);
  if (FAILED(hr)) {
    return false;
  }

  unsigned int num_modes;
  hr = adapter_output->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM,
                                          DXGI_ENUM_MODES_INTERLACED,
                                          &num_modes, NULL);
  if (FAILED(hr)) {
    return false;
  }

  DXGI_MODE_DESC* d_modes = new DXGI_MODE_DESC[num_modes];
  hr = adapter_output->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM,
                                          DXGI_ENUM_MODES_INTERLACED,
                                          &num_modes, d_modes);
  if (FAILED(hr)) {
    return false;
  }

  hr = device_->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM,
                                              4, &msaa_quality_);
  if (FAILED(hr)) {
    return false;
  }

  unsigned int numerator = 0, denominator = 1;
  if (vsync_enabled_)
    for (unsigned int i = 0; i < num_modes; i++)
      if (d_modes[i].Width == window->GetWidth())
        if (d_modes[i].Height == window->GetHeight()) {
          numerator = d_modes[i].RefreshRate.Numerator;
          denominator = d_modes[i].RefreshRate.Denominator;
        }

  DXGI_SWAP_CHAIN_DESC desc;
  memset(&desc, 0, sizeof(desc));
  desc.OutputWindow = window->GetHandle();
  desc.Windowed = !fullscreen_enabled_;
  desc.BufferDesc.Width = window->GetWidth();
  desc.BufferDesc.Height = window->GetHeight();
  desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  desc.BufferDesc.RefreshRate.Numerator = numerator;
  desc.BufferDesc.RefreshRate.Denominator = denominator;
  desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
  desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
  desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  desc.BufferCount = 1;
  desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
  desc.Flags = 0;
  desc.SampleDesc.Count = msaa_enabled_ ? 4 : 1;
  desc.SampleDesc.Quality = msaa_enabled_ ? msaa_quality_ - 1 : 0;

  hr = factory->CreateSwapChain(device_.get(), &desc, &swap_chain_);
  if (FAILED(hr)) {
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

  return true;
}

bool DirectX::CreateRenderTargetView() {
  HRESULT hr;

  ID3D11Texture2D* back_buffer;
  hr = swap_chain_->GetBuffer(
      0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&back_buffer));
  if (FAILED(hr)) return false;

  hr = device_->CreateRenderTargetView(
      back_buffer, nullptr, &render_target_view_);
  if (FAILED(hr)) return false;

  if (back_buffer) {
    back_buffer->Release();
    back_buffer = nullptr;
  }

  return true;
}

bool DirectX::CreateDepthBuffer(std::shared_ptr<Window> window) {
  HRESULT hr;

  D3D11_TEXTURE2D_DESC depth_buffer_desc;
  ZeroMemory(&depth_buffer_desc, sizeof(depth_buffer_desc));
  depth_buffer_desc.Width = window->GetWidth();
  depth_buffer_desc.Height = window->GetHeight();
  depth_buffer_desc.MipLevels = 1;
  depth_buffer_desc.ArraySize = 1;
  depth_buffer_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
  depth_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
  depth_buffer_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
  depth_buffer_desc.CPUAccessFlags = 0;
  depth_buffer_desc.MiscFlags = 0;
  depth_buffer_desc.SampleDesc.Quality = msaa_quality_ - 1;
  depth_buffer_desc.SampleDesc.Count = msaa_enabled_ ? 4 : 1;
  if (msaa_enabled_) {
    depth_buffer_desc.SampleDesc.Quality = msaa_quality_ - 1;
  } else {
    depth_buffer_desc.SampleDesc.Quality = 0;
  }

  hr = device_->CreateTexture2D(&depth_buffer_desc, nullptr,
                                &depth_stencil_buffer_);
  if (FAILED(hr)) {
    Log::Error("Failed to create back buffer");
    return false;
  }

  return true;
}

bool DirectX::CreateDepthStencilView() {
  D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc;
  ZeroMemory(&depth_stencil_view_desc, sizeof(depth_stencil_view_desc));
  depth_stencil_view_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
  depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
  depth_stencil_view_desc.Texture2D.MipSlice = 0;

  HRESULT hr = device_->CreateDepthStencilView(
      depth_stencil_buffer_, &depth_stencil_view_desc, &depth_stencil_view_);
  if (FAILED(hr)) {
    Log::Error("Failed to create depth stencil view");
    return false;
  }

  return true;
}

bool DirectX::CreateDepthStencilStates() {
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

  HRESULT hr = device_->CreateDepthStencilState(&depth_stencil_desc,
                                                &depth_stencil_state_);
  if (FAILED(hr)) {
    Log::Error("Failed to create depth stencil state");
    return false;
  }

  return true;
}

bool DirectX::CreateRasterizerStates() {
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

bool DirectX::CreateBlendStates() {
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

bool DirectX::CreateViewport(std::shared_ptr<Window> window) {
  D3D11_VIEWPORT viewport;
  memset(&viewport, 0, sizeof(viewport));
  viewport.Width = static_cast<float>(window->GetWidth());
  viewport.Height = static_cast<float>(window->GetHeight());
  viewport.MinDepth = 0;
  viewport.MaxDepth = 1;
  viewport.TopLeftX = 0;
  viewport.TopLeftY = 0;

  device_context_->RSSetViewports(1, &viewport);

  return true;
}
}  // namespace voodoo