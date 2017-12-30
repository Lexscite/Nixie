#include "mesh_data.h"

MeshData::MeshData()
{
	vertex_buffer_ = 0;
	index_buffer_ = 0;
	vertices_ = 0;
}

bool MeshData::Init(char * file_path)
{
	if (!LoadFile(file_path))
		return false;

	if (!InitBuffers())
		return false;

	return true;
}

void MeshData::Release()
{
	safe_release(index_buffer_);
	safe_release(vertex_buffer_);
	safe_delete_arr(vertices_);
}

bool MeshData::LoadFile(char * file_path)
{
	std::ifstream fin;
	fin.open(file_path);

	if (fin.fail())
		return false;

	char input;
	fin.get(input);
	while (input != ':')
		fin.get(input);

	fin >> vertex_count_;

	index_count_ = vertex_count_;

	vertices_ = new Vertex[vertex_count_];
	if (!vertices_)
		return false;

	fin.get(input);
	while (input != ':')
		fin.get(input);
	fin.get(input);
	fin.get(input);

	for (int i = 0; i < vertex_count_; i++)
	{
		fin >> vertices_[i].position.x >> vertices_[i].position.y >> vertices_[i].position.z;
		fin >> vertices_[i].texture.x >> vertices_[i].texture.y;
		fin >> vertices_[i].normal.x >> vertices_[i].normal.y >> vertices_[i].normal.z;
	}

	fin.close();

	return true;
}

int MeshData::GetIndexCount()
{
	return index_count_;
}

bool MeshData::InitBuffers()
{
	HRESULT result;

	unsigned long* indices = new unsigned long[index_count_];
	if (!indices)
		return false;

	for (int i = 0; i < vertex_count_; i++)
		indices[i] = i;

	D3D11_BUFFER_DESC vertex_buffer_desc;
	vertex_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	vertex_buffer_desc.ByteWidth = sizeof(Vertex) * vertex_count_;
	vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertex_buffer_desc.CPUAccessFlags = 0;
	vertex_buffer_desc.MiscFlags = 0;
	vertex_buffer_desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertex_buffer_data;
	vertex_buffer_data.pSysMem = vertices_;
	vertex_buffer_data.SysMemPitch = 0;
	vertex_buffer_data.SysMemSlicePitch = 0;

	ID3D11Device* device = D3D::GetSingleton()->GetDevice();
	result = device->CreateBuffer(&vertex_buffer_desc, &vertex_buffer_data, &vertex_buffer_);
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

	safe_delete_arr(indices);

	return true;
}

void MeshData::Render()
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(Vertex);
	offset = 0;

	ID3D11DeviceContext* device_context = D3D::GetSingleton()->GetDeviceContext();
	device_context->IASetVertexBuffers(0, 1, &vertex_buffer_, &stride, &offset);
	device_context->IASetIndexBuffer(index_buffer_, DXGI_FORMAT_R32_UINT, 0);
	device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}