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

#include "memory.h"

namespace voodoo {
struct Mesh;
class Scene;
class Window;

class GraphicsAPI {
 protected:
  using Device = ID3D11Device;
  using DeviceContext = ID3D11DeviceContext;

  using Buffer = ID3D11Buffer*;
  using MeshBuffer = pair<Buffer, Buffer>;
  using MeshBufferMap = map<sptr<Mesh>, MeshBuffer>;

 public:
  virtual ~GraphicsAPI() = default;

  virtual bool Init(const sptr<Window>& window) = 0;
  virtual bool Render(const sptr<Scene>& scene) = 0;
  virtual bool CreateMeshBuffers(sptr<Mesh> mesh) = 0;

  sptr<Device> GetDevice() { return device_; }
  sptr<DeviceContext> GetDeviceContext() { return device_context_; }
  MeshBufferMap GetMeshBuffers() { return mesh_buffers_; }

 protected:
  sptr<Device> device_;
  sptr<DeviceContext> device_context_;

  MeshBufferMap mesh_buffers_;
};
}  // namespace voodoo

#endif