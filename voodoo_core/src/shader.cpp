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

#include "../include/voodoo/shader.h"
#include "../include/voodoo/logger.h"

#ifdef VOODOO_DIRECTX
// Run-time shader compilation dependencies
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include <d3d11shader.h>
#include <d3dcompiler.h>
#endif  // VOODOO_DIRECTX

#include <vector>

namespace voodoo {
Shader::Shader(std::shared_ptr<ID3D11Device> device,
               std::shared_ptr<ID3D11DeviceContext> device_context)
    : vertex_shader_(nullptr),
      pixel_shader_(nullptr),
      input_layout_(nullptr),
      sampler_state_(nullptr),
      matrix_buffer_(nullptr),
      light_buffer_(nullptr),
      device_(device),
      device_context_(device_context) {}

Shader::~Shader() {
  if (vertex_shader_) {
    vertex_shader_->Release();
    vertex_shader_ = nullptr;
  }

  if (pixel_shader_) {
    pixel_shader_->Release();
    pixel_shader_ = nullptr;
  }

  if (input_layout_) {
    input_layout_->Release();
    input_layout_ = nullptr;
  }

  if (sampler_state_) {
    sampler_state_->Release();
    sampler_state_ = nullptr;
  }

  if (matrix_buffer_) {
    matrix_buffer_->Release();
    matrix_buffer_ = nullptr;
  }

  if (light_buffer_) {
    light_buffer_->Release();
    light_buffer_ = nullptr;
  }
}

bool Shader::Init(std::string vs_path, std::string ps_path, bool light) {
  HRESULT hr;

  light_ = light;

  auto vs_buffer = LoadFromFile(vs_path);
  auto ps_buffer = LoadFromFile(ps_path);

  hr = device_->CreateVertexShader(vs_buffer.data, vs_buffer.size, nullptr,
                                   &vertex_shader_);
  if (FAILED(hr)) {
    return false;
  }

  if (!CreateInputLayout(vs_buffer)) {
    return false;
  }

  if (!CreateMatrixBuffer()) {
    return false;
  }

  hr = device_->CreatePixelShader(ps_buffer.data, ps_buffer.size, nullptr,
                                  &pixel_shader_);
  if (FAILED(hr)) {
    return false;
  }

  if (!CreateSamplerState()) {
    return false;
  }

  if (light_) {
    if (!CreateLightBuffer()) {
      return false;
    }
  } else {
    D3D11_BUFFER_DESC pixelBufferDesc;
    pixelBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    pixelBufferDesc.ByteWidth = sizeof(PixelBuffer);
    pixelBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    pixelBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    pixelBufferDesc.MiscFlags = 0;
    pixelBufferDesc.StructureByteStride = 0;

    HRESULT result =
        device_->CreateBuffer(&pixelBufferDesc, NULL, &pixel_buffer_);
    if (FAILED(result)) {
      return false;
    }
  }

  delete[] vs_buffer.data;
  delete[] ps_buffer.data;

  return true;
}

bool Shader::Update(const Matrix4x4<float>& world_matrix,
                    const Matrix4x4<float>& view_matrix,
                    const Matrix4x4<float>& projection_matrix,
                    ID3D11ShaderResourceView* texture) {
  HRESULT hr;

  D3D11_MAPPED_SUBRESOURCE mapped_resource;

  hr = device_context_->Map(matrix_buffer_, 0, D3D11_MAP_WRITE_DISCARD, 0,
                            &mapped_resource);
  if (FAILED(hr)) {
    return false;
  }

  MatrixBuffer* matrix_buffer =
      static_cast<MatrixBuffer*>(mapped_resource.pData);
  matrix_buffer->world_matrix = world_matrix.Transpose();
  matrix_buffer->view_matrix = view_matrix.Transpose();
  matrix_buffer->projection_matrix = projection_matrix.Transpose();
  device_context_->Unmap(matrix_buffer_, 0);

  if (light_) {
    hr = device_context_->Map(light_buffer_, 0, D3D11_MAP_WRITE_DISCARD, 0,
                              &mapped_resource);
    if (FAILED(hr)) {
      return false;
    }

    LightBuffer* light_buffer =
        static_cast<LightBuffer*>(mapped_resource.pData);
    light_buffer->diffuse_color = Color(255, 255, 255);
    light_buffer->ambient_color = Color(55, 55, 55);
    light_buffer->direction = Vector3<float>(0, -1, 1);
    light_buffer->padding = 0.0f;
    device_context_->Unmap(light_buffer_, 0);
  } else {
    HRESULT result = device_context_->Map(
        pixel_buffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource);
    if (FAILED(result)) {
      return false;
    }

    PixelBuffer* dataPtr2 = (PixelBuffer*)mapped_resource.pData;
    dataPtr2->color = Color(255, 255, 255);
    device_context_->Unmap(pixel_buffer_, 0);
  }

  device_context_->VSSetConstantBuffers(0, 1, &matrix_buffer_);
  device_context_->VSSetShader(vertex_shader_, 0, 0);

  if (light_) {
    device_context_->PSSetConstantBuffers(0, 1, &light_buffer_);
  } else {
    device_context_->PSSetConstantBuffers(0, 1, &pixel_buffer_);
  }

  device_context_->PSSetSamplers(0, 1, &sampler_state_);
  device_context_->PSSetShaderResources(0, 1, &texture);
  device_context_->PSSetShader(pixel_shader_, 0, 0);

  device_context_->IASetInputLayout(input_layout_);

  return true;
}

Shader::ShaderBuffer Shader::LoadFromFile(std::string file_path) {
  std::ifstream fs;

  fs.open(file_path, std::ios::in | std::ios::binary);
  if (fs.fail()) {
    Log::Error("Error: Failed to open shader file ");
    throw std::runtime_error("Failed to open shader file");
  }

  fs.seekg(0, std::ios::end);
  auto size = static_cast<unsigned int>(fs.tellg());
  fs.seekg(0, std::ios::beg);

  ShaderBuffer buffer = ShaderBuffer(size);

  fs.read(reinterpret_cast<char*>(&buffer.data[0]), buffer.size);
  fs.close();

  return buffer;
}

bool Shader::CreateInputLayout(Shader::ShaderBuffer buffer) {
  HRESULT hr;

  ID3D11ShaderReflection* reflection = nullptr;
  hr = D3DReflect(buffer.data, buffer.size, IID_ID3D11ShaderReflection,
                  (void**)&reflection);
  if (FAILED(hr)) {
    Log::Error("Failed to reflect shader buffer");
    return false;
  }

  D3D11_SHADER_DESC shader_desc;
  hr = reflection->GetDesc(&shader_desc);
  if (FAILED(hr)) {
    Log::Error("Failed to get shader description");
    return false;
  }

  std::vector<D3D11_INPUT_ELEMENT_DESC> ieds;

  for (unsigned int i = 0; i < shader_desc.InputParameters; i++) {
    D3D11_SIGNATURE_PARAMETER_DESC param_desc;
    hr = reflection->GetInputParameterDesc(i, &param_desc);
    if (FAILED(hr)) {
      Log::Error("Failed to get input parameter description");
      return false;
    }

    D3D11_INPUT_ELEMENT_DESC ied;
    ied.SemanticName = param_desc.SemanticName;
    ied.SemanticIndex = param_desc.SemanticIndex;
    ied.InputSlot = 0;
    ied.AlignedByteOffset = i == 0 ? 0 : D3D11_APPEND_ALIGNED_ELEMENT;
    ied.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    ied.InstanceDataStepRate = 0;

    if (lstrcmpA(ied.SemanticName, LPCSTR("POSITION")) == 0) {
      ied.Format = DXGI_FORMAT_R32G32B32_FLOAT;
    } else if (param_desc.Mask == 1) {
      if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
        ied.Format = DXGI_FORMAT_R32_UINT;
      else if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
        ied.Format = DXGI_FORMAT_R32_SINT;
      else if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
        ied.Format = DXGI_FORMAT_R32_FLOAT;
    } else if (param_desc.Mask <= 3) {
      if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
        ied.Format = DXGI_FORMAT_R32G32_UINT;
      else if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
        ied.Format = DXGI_FORMAT_R32G32_SINT;
      else if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
        ied.Format = DXGI_FORMAT_R32G32_FLOAT;
    } else if (param_desc.Mask <= 7) {
      if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
        ied.Format = DXGI_FORMAT_R32G32B32_UINT;
      else if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
        ied.Format = DXGI_FORMAT_R32G32B32_SINT;
      else if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
        ied.Format = DXGI_FORMAT_R32G32B32_FLOAT;
    } else if (param_desc.Mask <= 15) {
      if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
        ied.Format = DXGI_FORMAT_R32G32B32A32_UINT;
      else if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
        ied.Format = DXGI_FORMAT_R32G32B32A32_SINT;
      else if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
        ied.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    }

    ieds.push_back(ied);
  }

  hr = device_->CreateInputLayout(ieds.data(),
                                  static_cast<unsigned int>(ieds.size()),
                                  buffer.data, buffer.size, &input_layout_);
  if (FAILED(hr)) {
    return false;
  }

  reflection->Release();

  return true;
}

bool Shader::CreateMatrixBuffer() {
  D3D11_BUFFER_DESC matrix_buffer_desc = {sizeof(MatrixBuffer),
                                          D3D11_USAGE_DYNAMIC,
                                          D3D11_BIND_CONSTANT_BUFFER,
                                          D3D11_CPU_ACCESS_WRITE,
                                          0,
                                          0};
  HRESULT hr =
      device_->CreateBuffer(&matrix_buffer_desc, nullptr, &matrix_buffer_);
  if (FAILED(hr)) {
    return false;
  }

  return true;
}

bool Shader::CreateSamplerState() {
  D3D11_SAMPLER_DESC sampler_desc = {D3D11_FILTER_MIN_MAG_MIP_LINEAR,
                                     D3D11_TEXTURE_ADDRESS_WRAP,
                                     D3D11_TEXTURE_ADDRESS_WRAP,
                                     D3D11_TEXTURE_ADDRESS_WRAP,
                                     0.0f,
                                     1,
                                     D3D11_COMPARISON_ALWAYS,
                                     {0.0f, 0.0f, 0.0f, 0.0f},
                                     0,
                                     D3D11_FLOAT32_MAX};
  HRESULT hr = device_->CreateSamplerState(&sampler_desc, &sampler_state_);
  if (FAILED(hr)) {
    return false;
  }

  return true;
}

bool Shader::CreateLightBuffer() {
  D3D11_BUFFER_DESC light_buffer_desc = {sizeof(LightBuffer),
                                         D3D11_USAGE_DYNAMIC,
                                         D3D11_BIND_CONSTANT_BUFFER,
                                         D3D11_CPU_ACCESS_WRITE,
                                         0,
                                         0};
  HRESULT hr =
      device_->CreateBuffer(&light_buffer_desc, nullptr, &light_buffer_);
  if (FAILED(hr)) {
    return false;
  }

  return true;
}
}  // namespace voodoo