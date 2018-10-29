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

#ifndef VOODOO_SHADER_H_
#define VOODOO_SHADER_H_

#include "color.h"
#include "directx.h"

namespace voodoo {
struct ShaderBuffer {
  ShaderBuffer(const uint& size) : data(new byte[size]), size(size) {}

  byte* data;
  uint size;
};

class Shader {
 private:
  struct MatrixBuffer {
    float4x4 world_matrix;
    float4x4 view_matrix;
    float4x4 projection_matrix;
  };

  struct LightBuffer {
    float4 diffuse_color;
    float4 ambient_color;
    float3 direction;
    float padding;
  };

  struct PixelBuffer {
    color color;
  };

 public:
  Shader(sptr<ID3D11Device> device, sptr<ID3D11DeviceContext> device_context);
  ~Shader();

  bool Init(const string& vs_path, const string& ps_path, bool light);
  bool Update(const float4x4& world_matrix,
              const float4x4& view_matrix,
              const float4x4& projection_matrix,
              ID3D11ShaderResourceView* texture);

 private:
  bool CreateInputLayout(sptr<ShaderBuffer> buffer);
  bool CreateMatrixBuffer();
  bool CreateLightBuffer();
  bool CreateSamplerState();

 private:
  sptr<ID3D11Device> device_;
  sptr<ID3D11DeviceContext> device_context_;

  ID3D11VertexShader* vertex_shader_;
  ID3D11PixelShader* pixel_shader_;
  ID3D11InputLayout* input_layout_;
  ID3D11SamplerState* sampler_state_;

  ID3D11Buffer* matrix_buffer_;
  ID3D11Buffer* light_buffer_;
  ID3D11Buffer* pixel_buffer_;

  bool light_;
};
}  // namespace voodoo

#endif  // VOODOO_SHADER_H_