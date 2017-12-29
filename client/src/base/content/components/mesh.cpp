#include "mesh.h"

Mesh::Mesh(char* file_path)
{
	file_path_ = file_path;
	vertex_buffer_ = 0;
	index_buffer_ = 0;
	vertices_ = 0;
}

void Mesh::OnInit()
{
	if (LoadFile())
		InitBuffers();
}

void Mesh::OnUpdate()
{
	UpdateVertices();
	RenderBuffers();
}

void Mesh::Release()
{
	safe_release(index_buffer_);
	safe_release(vertex_buffer_);
	safe_delete_arr(vertices_);
}

bool Mesh::LoadFile()
{
	std::ifstream fin;
	fin.open(file_path_);

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

int Mesh::GetIndexCount()
{
	return index_count_;
}

bool Mesh::InitBuffers()
{
	HRESULT result;

	UpdateVertices();

	ULONG* indices = new ULONG[index_count_];
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

	D3D11_SUBRESOURCE_DATA vertex_data;
	vertex_data.pSysMem = vertices_;
	vertex_data.SysMemPitch = 0;
	vertex_data.SysMemSlicePitch = 0;

	ID3D11Device* device = D3D::GetSingleton()->GetDevice();
	result = device->CreateBuffer(&vertex_buffer_desc, &vertex_data, &vertex_buffer_);
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

void Mesh::RenderBuffers()
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

void Mesh::UpdateVertices()
{
	for (int i = 0; i < vertex_count_; i++)
	{
		vertices_[i].position.x += GetGameObject()->GetPosition()->x;
		vertices_[i].position.y += GetGameObject()->GetPosition()->y;
		vertices_[i].position.z += GetGameObject()->GetPosition()->z;
	}
}