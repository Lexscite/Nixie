#include "../../stdafx.h"

#include "shader.h"
#include "../app.h"


namespace Nixie
{
	Shader::Shader() :
		vertex_shader_(nullptr),
		pixel_shader_(nullptr),
		input_layout_(nullptr),
		sampler_state_(nullptr),
		matrix_buffer_(nullptr),
		light_buffer_(nullptr) {}


	Shader::~Shader()
	{
		if (vertex_shader_)
		{
			vertex_shader_->Release();
			vertex_shader_ = nullptr;
		}

		if (pixel_shader_)
		{
			pixel_shader_->Release();
			pixel_shader_ = nullptr;
		}

		if (input_layout_)
		{
			input_layout_->Release();
			input_layout_ = nullptr;
		}

		if (sampler_state_)
		{
			sampler_state_->Release();
			sampler_state_ = nullptr;
		}

		if (matrix_buffer_)
		{
			matrix_buffer_->Release();
			matrix_buffer_ = nullptr;
		}

		if (light_buffer_)
		{
			light_buffer_->Release();
			light_buffer_ = nullptr;
		}
	}


	bool Shader::Init(std::string vs_path, std::string ps_path)
	{
		device_ = std::unique_ptr<ID3D11Device>(D3D::Get()->GetDevice());
		device_context_ = std::unique_ptr<ID3D11DeviceContext>(D3D::Get()->GetDeviceContext());

		auto vs_buffer = LoadFromFile(vs_path);
		auto ps_buffer = LoadFromFile(ps_path);

		if (!CreateVertexShader(vs_buffer))
		{
			return false;
		}

		if (!CreateInputLayout(vs_buffer))
		{
			return false;
		}

		if (!CreateMatrixBuffer())
		{
			return false;
		}

		if (!CreatePixelShader(ps_buffer))
		{
			return false;
		}

		if (!CreateSamplerState())
		{
			return false;
		}

		if (!CreateLightBuffer())
		{
			return false;
		}

		return true;
	}


	bool Shader::Update(const Matrix4x4<float>& world_matrix, ID3D11ShaderResourceView* texture)
	{
		HRESULT hr;

		D3D11_MAPPED_SUBRESOURCE mapped_resource;

		hr = device_context_->Map(matrix_buffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource);
		if (FAILED(hr))
		{
			return false;
		}

		MatrixBuffer* matrix_buffer = static_cast<MatrixBuffer*>(mapped_resource.pData);
		matrix_buffer->world_matrix = world_matrix.Transpose();
		matrix_buffer->view_matrix = App::GetScene()->GetCamera()->GetViewMatrix().Transpose();
		matrix_buffer->projection_matrix = App::GetScene()->GetCamera()->GetProjectionMatrix().Transpose();
		device_context_->Unmap(matrix_buffer_, 0);

		hr = device_context_->Map(light_buffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource);
		if (FAILED(hr))
		{
			return false;
		}

		LightBuffer* light_buffer = static_cast<LightBuffer*>(mapped_resource.pData);
		light_buffer->diffuse_color = Color(255, 255, 255);
		light_buffer->ambient_color = Color(55, 55, 55);
		light_buffer->direction = Vector3<float>(0, -1, 1);
		light_buffer->padding = 0.0f;
		device_context_->Unmap(light_buffer_, 0);

		device_context_->VSSetConstantBuffers(0, 1, &matrix_buffer_);
		device_context_->VSSetShader(vertex_shader_, 0, 0);

		device_context_->PSSetConstantBuffers(0, 1, &light_buffer_);
		device_context_->PSSetSamplers(0, 1, &sampler_state_);
		device_context_->PSSetShaderResources(0, 1, &texture);
		device_context_->PSSetShader(pixel_shader_, 0, 0);

		device_context_->IASetInputLayout(input_layout_);

		return true;
	}


	std::vector<unsigned char*> Shader::LoadFromFile(std::string file_path)
	{
		std::ifstream fs;

		fs.open(file_path, std::ios::in | std::ios::binary);
		if (fs.fail())
		{
			std::cerr << "Error: Failed to open shader file " << file_path << std::endl;
		}

		fs.seekg(0, std::ios::end);
		std::streampos size = fs.tellg();
		fs.seekg(0, std::ios::beg);

		auto buffer = std::vector<unsigned char*>(size, 0);
		buffer.reserve(size);

		fs.read(reinterpret_cast<char*>(&buffer[0]), size);
		fs.close();

		return buffer;
	}

	bool Shader::CreateVertexShader(std::vector<unsigned char*> buffer)
	{
		HRESULT hr = device_->CreateVertexShader(buffer.data(), buffer.size(), nullptr, &vertex_shader_);
		if (FAILED(hr))
		{
			return false;
		}

		return true;
	}


	bool Shader::CreateInputLayout(std::vector<unsigned char*> buffer)
	{
		D3D11_INPUT_ELEMENT_DESC polygon_layout[3];
		polygon_layout[0].SemanticName = "POSITION";
		polygon_layout[0].SemanticIndex = 0;
		polygon_layout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		polygon_layout[0].InputSlot = 0;
		polygon_layout[0].AlignedByteOffset = 0;
		polygon_layout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		polygon_layout[0].InstanceDataStepRate = 0;

		polygon_layout[1].SemanticName = "TEXCOORD";
		polygon_layout[1].SemanticIndex = 0;
		polygon_layout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
		polygon_layout[1].InputSlot = 0;
		polygon_layout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		polygon_layout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		polygon_layout[1].InstanceDataStepRate = 0;

		polygon_layout[2].SemanticName = "NORMAL";
		polygon_layout[2].SemanticIndex = 0;
		polygon_layout[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		polygon_layout[2].InputSlot = 0;
		polygon_layout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		polygon_layout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		polygon_layout[2].InstanceDataStepRate = 0;

		unsigned int num_elements = sizeof(polygon_layout) / sizeof(polygon_layout[0]);
		HRESULT hr = device_->CreateInputLayout(polygon_layout, num_elements, buffer.data(), buffer.size(), &input_layout_);
		if (FAILED(hr))
		{
			return false;
		}

		return true;
	}


	bool Shader::CreateMatrixBuffer()
	{
		D3D11_BUFFER_DESC matrix_buffer_desc;
		matrix_buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
		matrix_buffer_desc.ByteWidth = sizeof(MatrixBuffer);
		matrix_buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		matrix_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		matrix_buffer_desc.MiscFlags = 0;
		matrix_buffer_desc.StructureByteStride = 0;

		HRESULT hr = device_->CreateBuffer(&matrix_buffer_desc, nullptr, &matrix_buffer_);
		if (FAILED(hr))
		{
			return false;
		}

		return true;
	}


	bool Shader::CreatePixelShader(std::vector<unsigned char*> buffer)
	{
		HRESULT hr = device_->CreatePixelShader(buffer.data(), buffer.size(), nullptr, &pixel_shader_);
		if (FAILED(hr))
		{
			return false;
		}

		return true;
	}


	bool Shader::CreateSamplerState()
	{
		D3D11_SAMPLER_DESC sampler_desc;
		sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.MipLODBias = 0.0f;
		sampler_desc.MaxAnisotropy = 1;
		sampler_desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		sampler_desc.BorderColor[0] = 0;
		sampler_desc.BorderColor[1] = 0;
		sampler_desc.BorderColor[2] = 0;
		sampler_desc.BorderColor[3] = 0;
		sampler_desc.MinLOD = 0;
		sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;

		HRESULT hr = device_->CreateSamplerState(&sampler_desc, &sampler_state_);
		if (FAILED(hr))
		{
			return false;
		}

		return true;
	}


	bool Shader::CreateLightBuffer()
	{
		D3D11_BUFFER_DESC light_buffer_desc;
		light_buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
		light_buffer_desc.ByteWidth = sizeof(LightBuffer);
		light_buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		light_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		light_buffer_desc.MiscFlags = 0;
		light_buffer_desc.StructureByteStride = 0;

		HRESULT hr = device_->CreateBuffer(&light_buffer_desc, nullptr, &light_buffer_);
		if (FAILED(hr))
		{
			return false;
		}

		return true;
	}
}