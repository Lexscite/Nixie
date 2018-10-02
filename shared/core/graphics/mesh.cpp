#include "../../stdafx_core.h"

#include "mesh.h"
#include "core/logger.h"


namespace voodoo
{
	Mesh::Mesh() :
		device_(DirectXManager::Get()->GetDevice()),
		device_context_(DirectXManager::Get()->GetDeviceContext()),
		v_(),
		v_count_(0),
		i_(),
		i_count_(0),
		vertex_buffer_(nullptr),
		index_buffer_(nullptr)
	{}


	Mesh::Mesh(std::vector<VertexPTN> v) :
		device_(DirectXManager::Get()->GetDevice()),
		device_context_(DirectXManager::Get()->GetDeviceContext()),
		v_(v),
		v_count_(unsigned long(v.size())),
		i_(),
		i_count_(unsigned long(v_count_)),
		vertex_buffer_(nullptr),
		index_buffer_(nullptr)
	{
		for (unsigned long i = 0; i < i_count_; i++)
		{
			i_.push_back(i);
		}
	}


	bool Mesh::CreateBuffers()
	{
		if (!CreateVertexBuffer())
		{
			Logger::Write("Can't create vertex buffer");
			return false;
		}

		if (!CreateIndexBuffer())
		{
			Logger::Write("Can't create index buffer");
			return false;
		}

		return true;
	}


	unsigned long Mesh::GetVertexCount()
	{
		return v_count_;
	}


	unsigned long Mesh::GetIndexCount()
	{
		return i_count_;
	}


	std::vector<VertexPTN> Mesh::GetVertices()
	{
		return v_;
	}


	std::vector<unsigned long> Mesh::GetIndices()
	{
		return i_;
	}


	ID3D11Buffer* Mesh::GetVertexBuffer()
	{
		return vertex_buffer_;
	}


	ID3D11Buffer* Mesh::GetIndexBuffer()
	{
		return index_buffer_;
	}


	bool Mesh::CreateVertexBuffer()
	{
		D3D11_BUFFER_DESC vertex_buffer_desc;
		vertex_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
		vertex_buffer_desc.ByteWidth = sizeof(VertexPTN) * v_count_;
		vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertex_buffer_desc.CPUAccessFlags = 0;
		vertex_buffer_desc.MiscFlags = 0;
		vertex_buffer_desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA vertex_buffer_data;
		vertex_buffer_data.pSysMem = v_.data();
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
		index_buffer_desc.ByteWidth = sizeof(unsigned long) * i_count_;
		index_buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		index_buffer_desc.CPUAccessFlags = 0;
		index_buffer_desc.MiscFlags = 0;
		index_buffer_desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA index_data;
		index_data.pSysMem = i_.data();
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
