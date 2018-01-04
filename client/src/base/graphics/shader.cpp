#include "shader.h"
#include "..\app.h"

Shader::Shader()
{
	vertex_shader_ = nullptr;
	pixel_shader_ = nullptr;
	layout_ = nullptr;
	matrix_buffer_ = nullptr;
	sampler_state_ = nullptr;
}

void Shader::Release()
{
	safe_release(matrix_buffer_);
	safe_release(layout_);
	safe_release(pixel_shader_);
	safe_release(vertex_shader_);
	safe_release(sampler_state_);
}

bool Shader::Init(WCHAR* file_path)
{
	HRESULT hr;
	ID3D10Blob* error_message = 0;

	ID3D10Blob* vertex_shader_buffer = 0;
	hr = D3DCompileFromFile(
		file_path,
		0, 0,
		"DefaultVertexShader",
		"vs_4_0",
		D3D10_SHADER_ENABLE_STRICTNESS,
		0,
		&vertex_shader_buffer,
		&error_message);
	if (FAILED(hr))
	{
		if (error_message)
			OutputShaderErrorMessage(error_message, file_path);
		else
			MessageBox(App::GetSingleton()->GetHwnd(), (LPCSTR)(file_path), "Missing Shader File", MB_OK);

		return false;
	}

	ID3D10Blob* pixel_shader_buffer = 0;
	hr = D3DCompileFromFile(
		file_path,
		0, 0,
		"DefaultPixelShader",
		"ps_4_0",
		D3D10_SHADER_ENABLE_STRICTNESS,
		0,
		&pixel_shader_buffer,
		&error_message);
	if (FAILED(hr))
	{
		if (error_message)
			OutputShaderErrorMessage(error_message, file_path);
		else
			MessageBox(App::GetSingleton()->GetHwnd(), (LPCSTR)file_path, "Missing Shader File", MB_OK);

		return false;
	}

	ID3D11Device* device = D3D::GetSingleton()->GetDevice();
	hr = device->CreateVertexShader(
		vertex_shader_buffer->GetBufferPointer(),
		vertex_shader_buffer->GetBufferSize(),
		0,
		&vertex_shader_);
	if (FAILED(hr))
		return false;

	hr = device->CreatePixelShader(
		pixel_shader_buffer->GetBufferPointer(),
		pixel_shader_buffer->GetBufferSize(),
		NULL,
		&pixel_shader_);
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

	polygon_layout[2].SemanticName = "COLOR";
	polygon_layout[2].SemanticIndex = 0;
	polygon_layout[2].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygon_layout[2].InputSlot = 0;
	polygon_layout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygon_layout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygon_layout[2].InstanceDataStepRate = 0;

	UINT num_elements = sizeof(polygon_layout) / sizeof(polygon_layout[0]);
	hr = device->CreateInputLayout(polygon_layout, num_elements, vertex_shader_buffer->GetBufferPointer(),
		vertex_shader_buffer->GetBufferSize(), &layout_);
	if (FAILED(hr))
		return false;

	safe_release(vertex_shader_buffer);
	safe_release(pixel_shader_buffer);

	D3D11_BUFFER_DESC matrix_buffer_desc;
	matrix_buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
	matrix_buffer_desc.ByteWidth = sizeof(MatrixBuffer);
	matrix_buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrix_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrix_buffer_desc.MiscFlags = 0;
	matrix_buffer_desc.StructureByteStride = 0;

	hr = device->CreateBuffer(&matrix_buffer_desc, NULL, &matrix_buffer_);
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

	hr = device->CreateSamplerState(&sampler_desc, &sampler_state_);
	if (FAILED(hr))
		return false;

	return true;
}

bool Shader::Update(Matrix world_matrix, Matrix view_matrix, Matrix projection_matrix, ID3D11ShaderResourceView* texture)
{
	ID3D11DeviceContext* device_context = D3D::GetSingleton()->GetDeviceContext();

	world_matrix = XMMatrixTranspose(world_matrix);
	view_matrix = XMMatrixTranspose(view_matrix);
	projection_matrix = XMMatrixTranspose(projection_matrix);

	D3D11_MAPPED_SUBRESOURCE mapped_resource;
	HRESULT result = device_context->Map(matrix_buffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource);
	if (FAILED(result))
		return false;

	MatrixBuffer* data;
	data = (MatrixBuffer*)mapped_resource.pData;
	data->world_matrix = world_matrix;
	data->view_matrix = view_matrix;
	data->projection_matrix = projection_matrix;

	device_context->Unmap(matrix_buffer_, 0);

	UINT buffer_num = 0;
	device_context->PSSetShaderResources(0, 1, &texture);
	device_context->VSSetConstantBuffers(buffer_num, 1, &matrix_buffer_);
	device_context->IASetInputLayout(layout_);
	device_context->VSSetShader(vertex_shader_, 0, 0);
	device_context->PSSetShader(pixel_shader_, 0, 0);
	device_context->PSSetSamplers(0, 1, &sampler_state_);

	return true;
}

void Shader::OutputShaderErrorMessage(ID3D10Blob* error_message, WCHAR* shader_path)
{
	char* compile_errors;
	unsigned long long bufferSize, i;
	std::ofstream fout;


	compile_errors = static_cast<char*>(error_message->GetBufferPointer());

	bufferSize = error_message->GetBufferSize();

	fout.open("shader-error.txt");

	for (i = 0; i < bufferSize; i++)
		fout << compile_errors[i];

	fout.close();

	safe_release(error_message);

	MessageBox(App::GetSingleton()->GetHwnd(), "Error compiling shader.  Check shader-error.txt for message.", (LPCSTR)shader_path, MB_OK);
}