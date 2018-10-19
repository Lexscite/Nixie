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

#ifndef VOODOO_GRAPHICS_API_H_
#define VOODOO_GRAPHICS_API_H_

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

#include <map>
#include <memory>

namespace voodoo {
class Camera;
class Renderer;
class Window;
struct Mesh;

class GraphicsAPI {
 protected:
  using DevicePtr = std::shared_ptr<ID3D11Device>;
  using DeviceContextPtr = std::shared_ptr<ID3D11DeviceContext>;

  using MeshBufferPtr = ID3D11Buffer*;
  using MeshBufferPair = std::pair<MeshBufferPtr, MeshBufferPtr>;
  using MeshBufferMap = std::map<std::shared_ptr<Mesh>, MeshBufferPair>;

 public:
  virtual bool Init(std::shared_ptr<Window> window) = 0;
  virtual bool Render(std::shared_ptr<Renderer> renderer,
                      std::shared_ptr<Camera> camera) = 0;
  virtual bool CreateMeshBuffers(std::shared_ptr<Mesh> mesh) = 0;

  DevicePtr GetDevice() { return device_; }
  DeviceContextPtr GetDeviceContext() { return device_context_; }
  MeshBufferMap GetMeshBuffers() { return mesh_buffers_; }

 protected:
  DevicePtr device_;
  DeviceContextPtr device_context_;

  MeshBufferMap mesh_buffers_;
};
}  // namespace voodoo

#endif