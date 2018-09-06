#include "../../stdafx.h"

#include "mesh.h"


namespace Nixie
{
	Mesh::Mesh() :
		vertex_buffer_(nullptr),
		index_buffer_(nullptr) {}


	Mesh::~Mesh()
	{
		if (vertex_buffer_)
		{
			vertex_buffer_->Release();
			vertex_buffer_ = nullptr;
		}

		if (index_buffer_)
		{
			index_buffer_->Release();
			index_buffer_ = nullptr;
		}
	}


	bool Mesh::Init(std::string file_path)
	{
		device_ = std::shared_ptr<ID3D11Device>(D3D::GetSingleton()->GetDevice());
		device_context_ = std::shared_ptr<ID3D11DeviceContext>(D3D::GetSingleton()->GetDeviceContext());

		if (!LoadFromFile(file_path))
		{
			return false;
		}

		if (!CreateVertexBuffer())
		{
			return false;
		}

		if (!CreateIndexBuffer())
		{
			return false;
		}

		return true;
	}


	void Mesh::Render()
	{
		unsigned int stride = sizeof(Vertex);
		unsigned int offset = 0;

		device_context_->IASetVertexBuffers(0, 1, &vertex_buffer_, &stride, &offset);
		device_context_->IASetIndexBuffer(index_buffer_, DXGI_FORMAT_R32_UINT, 0);
		device_context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		device_context_->DrawIndexed(index_count_, 0, 0);
	}


	bool Mesh::LoadFromFile(std::string file_path)
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

		fin.get(input);
		while (input != ':')
			fin.get(input);
		fin.get(input);
		fin.get(input);

		for (unsigned int i = 0; i < vertex_count_; i++)
		{
			fin >>
				vertices_[i].position.x >>
				vertices_[i].position.y >>
				vertices_[i].position.z;
			fin >>
				vertices_[i].texture.x >>
				vertices_[i].texture.y;
			fin >>
				vertices_[i].normal.x >>
				vertices_[i].normal.y >>
				vertices_[i].normal.z;
		}

		fin.close();

		indices_ = new unsigned long[index_count_];
		for (unsigned int i = 0; i < vertex_count_; i++)
			indices_[i] = i;

		return true;
	}


	bool Mesh::CreateVertexBuffer()
	{
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

		HRESULT hr = device_->CreateBuffer(&vertex_buffer_desc, &vertex_buffer_data, &vertex_buffer_);
		if (FAILED(hr))
		{
			return false;
		}

		return true;
	}


	bool Mesh::CreateIndexBuffer()
	{
		D3D11_BUFFER_DESC index_buffer_desc;
		index_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
		index_buffer_desc.ByteWidth = sizeof(unsigned long) * index_count_;
		index_buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		index_buffer_desc.CPUAccessFlags = 0;
		index_buffer_desc.MiscFlags = 0;
		index_buffer_desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA index_data;
		index_data.pSysMem = indices_;
		index_data.SysMemPitch = 0;
		index_data.SysMemSlicePitch = 0;

		HRESULT hr = device_->CreateBuffer(&index_buffer_desc, &index_data, &index_buffer_);
		if (FAILED(hr))
		{
			return false;
		}

		return true;
	}
}