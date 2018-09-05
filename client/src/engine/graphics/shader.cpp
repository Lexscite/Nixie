#include "../../stdafx.h"

#include "shader.h"
#include "../app.h"


namespace Nixie
{
	Shader::Shader() :
		vertex_shader(nullptr),
		pixel_shader(nullptr),
		layout(nullptr),
		matrix_buffer(nullptr),
		sampler_state(nullptr) {}


	void Shader::Release()
	{
		if (matrix_buffer)
		{
			matrix_buffer->Release();
			matrix_buffer = nullptr;
		}

		if (layout)
		{
			layout->Release();
			layout = nullptr;
		}

		if (pixel_shader)
		{
			pixel_shader->Release();
			pixel_shader = nullptr;
		}

		if (vertex_shader)
		{
			vertex_shader->Release();
			vertex_shader = nullptr;
		}

		if (sampler_state)
		{
			sampler_state->Release();
			sampler_state = nullptr;
		}
	}


	bool Shader::Init(std::string vs_path, std::string ps_path)
	{
		if (!InitVS(ReadCSO(vs_path)))
			return false;

		if (!InitPS(ReadCSO(ps_path)))
			return false;

		return true;
	}


	std::vector<unsigned char*> Shader::ReadCSO(std::string file_path)
	{
		std::ifstream fs;
		fs.open(file_path, std::ios::in | std::ios::binary);
		fs.unsetf(std::ios::skipws);

		fs.seekg(0, std::ios::end);
		std::streampos size = fs.tellg();
		fs.seekg(0, std::ios::beg);

		std::vector<unsigned char*> data(size, 0);
		data.reserve(size);

		fs.read(reinterpret_cast<char*>(&data[0]), size);

		fs.close();

		return data;
	}


	bool Shader::InitVS(std::vector<unsigned char*> shader_data)
	{
		HRESULT hr;

		ID3D11Device* device = D3D::GetSingleton()->GetDevice();
		hr = device->CreateVertexShader(
			shader_data.data(),
			shader_data.size(),
			nullptr,
			&vertex_shader);
		if (FAILED(hr))
			return false;

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

		UINT num_elements = sizeof(polygon_layout) / sizeof(polygon_layout[0]);
		hr = device->CreateInputLayout(
			polygon_layout,
			num_elements,
			shader_data.data(),
			shader_data.size(),
			&layout);
		if (FAILED(hr))
			return false;

		D3D11_BUFFER_DESC matrix_buffer_desc;
		matrix_buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
		matrix_buffer_desc.ByteWidth = sizeof(MatrixBuffer);
		matrix_buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		matrix_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		matrix_buffer_desc.MiscFlags = 0;
		matrix_buffer_desc.StructureByteStride = 0;

		hr = device->CreateBuffer(&matrix_buffer_desc, NULL, &matrix_buffer);
		if (FAILED(hr))
			return false;

		return true;
	}


	bool Shader::InitPS(std::vector<unsigned char*> shader_data)
	{
		HRESULT hr;

		ID3D11Device* device = D3D::GetSingleton()->GetDevice();
		hr = device->CreatePixelShader(
			shader_data.data(),
			shader_data.size(),
			NULL,
			&pixel_shader);
		if (FAILED(hr))
			return false;

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

		hr = device->CreateSamplerState(&sampler_desc, &sampler_state);
		if (FAILED(hr))
			return false;

		D3D11_BUFFER_DESC light_buffer_desc;
		light_buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
		light_buffer_desc.ByteWidth = sizeof(LightBuffer);
		light_buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		light_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		light_buffer_desc.MiscFlags = 0;
		light_buffer_desc.StructureByteStride = 0;

		hr = device->CreateBuffer(&light_buffer_desc, NULL, &light_buffer);
		if (FAILED(hr))
			return false;

		return true;
	}


	void Shader::SetTexture(ID3D11ShaderResourceView* texture)
	{
		D3D::GetSingleton()->GetDeviceContext()->PSSetShaderResources(0, 1, &texture);
	}


	bool Shader::Update(DirectX::SimpleMath::Matrix world_matrix)
	{
		ID3D11DeviceContext* device_context = D3D::GetSingleton()->GetDeviceContext();

		D3D11_MAPPED_SUBRESOURCE mapped_resource;
		HRESULT result = device_context->Map(this->matrix_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource);
		if (FAILED(result))
			return false;

		MatrixBuffer* matrix_buffer;
		matrix_buffer = (MatrixBuffer*)mapped_resource.pData;
		matrix_buffer->world_matrix = XMMatrixTranspose(world_matrix);
		matrix_buffer->view_matrix = XMMatrixTranspose(App::GetSingleton()->GetScene()->GetCamera()->GetViewMatrix());
		matrix_buffer->projection_matrix = XMMatrixTranspose(D3D::GetSingleton()->GetProjectionMatrix());
		device_context->Unmap(this->matrix_buffer, 0);

		device_context->VSSetConstantBuffers(0, 1, &this->matrix_buffer);
		device_context->VSSetShader(this->vertex_shader, 0, 0);

		result = device_context->Map(this->light_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource);
		if (FAILED(result))
			return false;

		LightBuffer* light_buffer = (LightBuffer*)mapped_resource.pData;
		light_buffer->diffuse_color = DirectX::SimpleMath::Color(1, 1, 1);
		light_buffer->ambient_color = DirectX::SimpleMath::Color(0.2f, 0.2f, 0.2f);
		light_buffer->direction = DirectX::SimpleMath::Vector3(0, -1, 1);
		light_buffer->padding = 0.0f;
		device_context->Unmap(this->light_buffer, 0);

		device_context->PSSetConstantBuffers(0, 1, &this->light_buffer);
		device_context->PSSetSamplers(0, 1, &sampler_state);
		device_context->PSSetShader(pixel_shader, 0, 0);

		device_context->IASetInputLayout(layout);

		return true;
	}
}