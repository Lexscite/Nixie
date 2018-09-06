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


	bool Mesh::Init(unsigned long vertex_count, unsigned long index_count, Vertex* vertices, unsigned long* indices)
	{
		device_ = std::shared_ptr<ID3D11Device>(D3D::GetSingleton()->GetDevice());
		device_context_ = std::shared_ptr<ID3D11DeviceContext>(D3D::GetSingleton()->GetDeviceContext());

		if (!CreateVertexBuffer(vertices, vertex_count))
		{
			return false;
		}

		if (!CreateIndexBuffer(indices, index_count))
		{
			return false;
		}

		return true;
	}


	void Mesh::Render(unsigned long index_count, D3D11_PRIMITIVE_TOPOLOGY format)
	{
		unsigned int stride = sizeof(Vertex);
		unsigned int offset = 0;

		device_context_->IASetVertexBuffers(0, 1, &vertex_buffer_, &stride, &offset);
		device_context_->IASetIndexBuffer(index_buffer_, DXGI_FORMAT_R32_UINT, 0);
		device_context_->IASetPrimitiveTopology(format);

		device_context_->DrawIndexed(index_count, 0, 0);
	}


	bool Mesh::CreateVertexBuffer(Vertex* vertices, unsigned long vertex_count)
	{
		D3D11_BUFFER_DESC vertex_buffer_desc;
		vertex_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
		vertex_buffer_desc.ByteWidth = sizeof(Vertex) * vertex_count;
		vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertex_buffer_desc.CPUAccessFlags = 0;
		vertex_buffer_desc.MiscFlags = 0;
		vertex_buffer_desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA vertex_buffer_data;
		vertex_buffer_data.pSysMem = vertices;
		vertex_buffer_data.SysMemPitch = 0;
		vertex_buffer_data.SysMemSlicePitch = 0;

		HRESULT hr = device_->CreateBuffer(&vertex_buffer_desc, &vertex_buffer_data, &vertex_buffer_);
		if (FAILED(hr))
		{
			return false;
		}

		return true;
	}


	bool Mesh::CreateIndexBuffer(unsigned long* indices, unsigned long index_count)
	{
		D3D11_BUFFER_DESC index_buffer_desc;
		index_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
		index_buffer_desc.ByteWidth = sizeof(unsigned long) * index_count;
		index_buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		index_buffer_desc.CPUAccessFlags = 0;
		index_buffer_desc.MiscFlags = 0;
		index_buffer_desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA index_data;
		index_data.pSysMem = indices;
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