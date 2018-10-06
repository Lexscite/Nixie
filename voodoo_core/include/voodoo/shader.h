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

#ifndef VOODOO_SHADER_H_
#define VOODOO_SHADER_H_

#include "color.h"
#include "directx_manager.h"
#include "matrix.h"
#include "vector.h"

#include <string>

namespace voodoo {
class Shader {
 private:
  struct ShaderBuffer {
    ShaderBuffer(unsigned int size) : data(new byte[size]), size(size) {}

    byte* data;
    unsigned int size;
  };

  struct MatrixBuffer {
    Matrix4x4<float> world_matrix;
    Matrix4x4<float> view_matrix;
    Matrix4x4<float> projection_matrix;
  };

  struct LightBuffer {
    Color diffuse_color;
    Color ambient_color;
    Vector3<float> direction;
    float padding;
  };

  struct PixelBuffer {
    Color color;
  };

 public:
  Shader();
  ~Shader();

  bool Init(std::string vs_path, std::string ps_path, bool light);
  bool Update(const Matrix4x4<float>& world_matrix,
              const Matrix4x4<float>& view_matrix,
              const Matrix4x4<float>& projection_matrix,
              ID3D11ShaderResourceView* texture);

 private:
  bool CreateInputLayout(ShaderBuffer buffer);
  bool CreateMatrixBuffer();
  bool CreateSamplerState();
  bool CreateLightBuffer();

  ShaderBuffer LoadFromFile(std::string file_path);

 private:
  std::shared_ptr<ID3D11Device> device_;
  std::shared_ptr<ID3D11DeviceContext> device_context_;

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

#endif