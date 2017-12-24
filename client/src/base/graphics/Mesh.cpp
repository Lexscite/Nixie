#include "Mesh.h"

Mesh::Mesh()
{
	vertex_buffer_ = 0;
	index_buffer_ = 0;
	data_ = 0;
}

bool Mesh::Init(char* file_path)
{
	if (!LoadFile(file_path))
	{
		return false;
		std::cerr << "Failed to load mesh" << std::endl;
	}

	if (!InitBuffers())
	{
		std::cerr << "Failed to load buffers" << std::endl;
		return false;
	}

	return true;
}

void Mesh::Release()
{
	safe_release(index_buffer_);
	safe_release(vertex_buffer_);
	safe_delete_arr(data_);
}

bool Mesh::LoadFile(char* filePath)
{
	std::ifstream fin;
	fin.open(filePath);

	if (fin.fail())
		return false;

	char input;
	fin.get(input);
	while (input != ':')
		fin.get(input);

	fin >> vertex_count_;

	index_count_ = vertex_count_;

	data_ = new ModelType[vertex_count_];
	if (!data_)
		return false;

	fin.get(input);
	while (input != ':')
		fin.get(input);
	fin.get(input);
	fin.get(input);

	for (size_t i = 0; i < vertex_count_; i++)
	{
		fin >> data_[i].x >> data_[i].y >> data_[i].z;
		fin >> data_[i].nx >> data_[i].ny >> data_[i].nz;
	}

	fin.close();

	return true;
}

void Mesh::Render()
{
	RenderBuffers();
}

int Mesh::GetIndexCount()
{
	return index_count_;
}

bool Mesh::InitBuffers()
{
	vertex_count_ = 3;
	index_count_ = 3;

	VertexType* vertices = new VertexType[vertex_count_];
	if (!vertices)
		return false;

	ULONG* indices = new ULONG[index_count_];
	if (!indices)
		return false;

	for  (size_t i = 0; i < vertex_count_; i++)
	{
		vertices[i].position = Vector3(data_[i].x, data_[i].y, data_[i].z);
		vertices[i].normal = Vector3(data_[i].nx, data_[i].ny, data_[i].nz);

		indices[i] = (ULONG)i;
	}

	D3D11_BUFFER_DESC vertex_buffer_desc;
	vertex_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	vertex_buffer_desc.ByteWidth = sizeof(VertexType) * vertex_count_;
	vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertex_buffer_desc.CPUAccessFlags = 0;
	vertex_buffer_desc.MiscFlags = 0;
	vertex_buffer_desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertex_data;
	vertex_data.pSysMem = vertices;
	vertex_data.SysMemPitch = 0;
	vertex_data.SysMemSlicePitch = 0;

	ID3D11Device* device = D3D::GetSingleton()->GetDevice();
	HRESULT result = device->CreateBuffer(&vertex_buffer_desc, &vertex_data, &vertex_buffer_);
	if (FAILED(result))
		return false;

	D3D11_BUFFER_DESC index_buffer_desc;
	index_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	index_buffer_desc.ByteWidth = sizeof(unsigned long) * index_count_;
	index_buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	index_buffer_desc.CPUAccessFlags = 0;
	index_buffer_desc.MiscFlags = 0;
	index_buffer_desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA index_data;
	index_data.pSysMem = indices;
	index_data.SysMemPitch = 0;
	index_data.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&index_buffer_desc, &index_data, &index_buffer_);
	if (FAILED(result))
		return false;

	safe_delete_arr(vertices);
	safe_delete_arr(indices);

	return true;
}

void Mesh::RenderBuffers()
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(VertexType);
	offset = 0;

	ID3D11DeviceContext* device_context = D3D::GetSingleton()->GetDeviceContext();

	device_context->IASetVertexBuffers(0, 1, &vertex_buffer_, &stride, &offset);
	device_context->IASetIndexBuffer(index_buffer_, DXGI_FORMAT_R32_UINT, 0);
	device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}