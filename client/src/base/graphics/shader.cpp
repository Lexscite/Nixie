#include "shader.h"
#include "..\app.h"

Shader::Shader()
{
	vertex_shader_ = nullptr;
	pixel_shader_ = nullptr;
	layout_ = nullptr;
	matrix_buffer_ = nullptr;
}

void Shader::Release()
{
	safe_release(matrix_buffer_);
	safe_release(layout_);
	safe_release(pixel_shader_);
	safe_release(vertex_shader_);
}

bool Shader::Init(WCHAR* file_path)
{
	HRESULT result;
	ID3D10Blob* error_message = 0;
	
	ID3D10Blob* vertex_shader_buffer = 0;
	result = D3DCompileFromFile(file_path, 0, 0, "DefaultVertexShader", "vs_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
		&vertex_shader_buffer, &error_message);
	if (FAILED(result))
	{
		if (error_message)
			OutputShaderErrorMessage(error_message, file_path);
		else
			MessageBox(App::GetSingleton()->GetHwnd(), (LPCSTR)(file_path), "Missing Shader File", MB_OK);

		return false;
	}

	ID3D10Blob* pixel_shader_buffer = 0;
	result = D3DCompileFromFile(file_path, 0, 0, "DefaultPixelShader", "ps_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
		&pixel_shader_buffer, &error_message);
	if (FAILED(result))
	{
		if (error_message)
			OutputShaderErrorMessage(error_message, file_path);
		else
			MessageBox(App::GetSingleton()->GetHwnd(), (LPCSTR)file_path, "Missing Shader File", MB_OK);

		return false;
	}

	ID3D11Device* device = D3D::GetSingleton()->GetDevice();
	result = device->CreateVertexShader(vertex_shader_buffer->GetBufferPointer(), vertex_shader_buffer->GetBufferSize(), 0, &vertex_shader_);
	if (FAILED(result))
		return false;

	result = device->CreatePixelShader(pixel_shader_buffer->GetBufferPointer(), pixel_shader_buffer->GetBufferSize(), NULL, &pixel_shader_);
	if (FAILED(result))
		return false;

	D3D11_INPUT_ELEMENT_DESC polygon_layout[2];
	polygon_layout[0].SemanticName = "POSITION";
	polygon_layout[0].SemanticIndex = 0;
	polygon_layout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygon_layout[0].InputSlot = 0;
	polygon_layout[0].AlignedByteOffset = 0;
	polygon_layout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygon_layout[0].InstanceDataStepRate = 0;

	polygon_layout[1].SemanticName = "COLOR";
	polygon_layout[1].SemanticIndex = 0;
	polygon_layout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygon_layout[1].InputSlot = 0;
	polygon_layout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygon_layout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygon_layout[1].InstanceDataStepRate = 0;

	UINT num_elements = sizeof(polygon_layout) / sizeof(polygon_layout[0]);
	result = device->CreateInputLayout(polygon_layout, num_elements, vertex_shader_buffer->GetBufferPointer(),
		vertex_shader_buffer->GetBufferSize(), &layout_);
	if (FAILED(result))
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

	result = device->CreateBuffer(&matrix_buffer_desc, NULL, &matrix_buffer_);
	if (FAILED(result))
		return false;

	return true;
}

bool Shader::Update(XMMATRIX world_matrix, XMMATRIX view_matrix, XMMATRIX projection_matrix)
{
	world_matrix = XMMatrixTranspose(world_matrix);
	view_matrix = XMMatrixTranspose(view_matrix);
	projection_matrix = XMMatrixTranspose(projection_matrix);

	D3D11_MAPPED_SUBRESOURCE mapped_resource;
	ID3D11DeviceContext* device_context = D3D::GetSingleton()->GetDeviceContext();
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
	device_context->VSSetConstantBuffers(buffer_num, 1, &matrix_buffer_);
	device_context->IASetInputLayout(layout_);
	device_context->VSSetShader(vertex_shader_, 0, 0);
	device_context->PSSetShader(pixel_shader_, 0, 0);

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

	error_message->Release();
	error_message = 0;

	MessageBox(App::GetSingleton()->GetHwnd(), "Error compiling shader.  Check shader-error.txt for message.", (LPCSTR)shader_path, MB_OK);
}