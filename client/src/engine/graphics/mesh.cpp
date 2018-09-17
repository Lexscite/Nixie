#include "../../stdafx.h"

#include "mesh.h"


namespace nixie
{
	Mesh::Mesh(std::string file_path) :
		device_(DirectXManager::Get()->GetDevice()),
		device_context_(DirectXManager::Get()->GetDeviceContext()),
		v_(),
		v_count_(0),
		i_(),
		i_count_(0),
		vertex_buffer_(nullptr),
		index_buffer_(nullptr)
	{
		if (!LoadFromFile(file_path))
		{
			Logger::Write("Couldn't open mesh file: \"" + file_path + "\"");
			throw std::runtime_error("Couldn't open mesh file: \"" + file_path + "\"");
		}
	}


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


	bool Mesh::Init()
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


	void Mesh::Render()
	{
		unsigned int stride = sizeof(VertexPTN);
		unsigned int offset = 0;

		device_context_->IASetVertexBuffers(0, 1, &vertex_buffer_, &stride, &offset);
		device_context_->IASetIndexBuffer(index_buffer_, DXGI_FORMAT_R32_UINT, 0);
		device_context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		device_context_->DrawIndexed(i_count_, 0, 0);
	}


	bool Mesh::LoadFromFile(const std::string& file_path)
	{
		std::ifstream fin;
		fin.open(file_path);

		if (fin.fail())
			return false;

		char input;

		fin.get(input);
		while (input != ':')
			fin.get(input);

		fin >> v_count_;

		i_count_ = v_count_;

		v_.resize(v_count_);
		i_.resize(i_count_);

		fin.get(input);
		while (input != ':')
			fin.get(input);
		fin.get(input);
		fin.get(input);

		for (unsigned int i = 0; i < v_count_; i++)
		{
			fin >>
				v_[i].position.x >>
				v_[i].position.y >>
				v_[i].position.z;
			fin >>
				v_[i].texture.x >>
				v_[i].texture.y;
			fin >>
				v_[i].normal.x >>
				v_[i].normal.y >>
				v_[i].normal.z;
		}


		fin.close();

		for (unsigned long i = 0; i < i_count_; i++)
			i_[i] = i;

		return true;
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
