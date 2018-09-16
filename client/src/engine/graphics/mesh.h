#ifndef NIXIE_MESH_H_
#define NIXIE_MESH_H_

#pragma once

#include "directx_manager.h"
#include "vertex.h"
#include "../logger.h"


namespace Nixie
{
	template <class T>
	struct MeshData
	{
		MeshData() = default;

		MeshData(std::vector<T> v, std::vector<unsigned long> i) :
			v_(v),
			v_count_(unsigned long(v.size())),
			i_(i),
			i_count_(unsigned long(i.size()))
		{}

		std::vector<T> v_;
		unsigned long v_count_;

		std::vector<unsigned long> i_;
		unsigned long i_count_;
	};


	template<class T>
	class Mesh
	{
	public:
		Mesh() :
			device_(DirectXManager::Get()->GetDevice()),
			device_context_(DirectXManager::Get()->GetDeviceContext()),
			data_(),
			vertex_buffer_(nullptr),
			index_buffer_(nullptr)
		{}

		bool Init(const std::vector<T>& vertices)
		{
			std::vector<unsigned long> indices;
			indices.resize(vertices.size());

			for (unsigned long i = 0; i < vertices.size(); i++)
			{
				indices[i] = i;
			}

			data_ = MeshData<T>(vertices, indices);

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

		bool Init(const std::string& file_path)
		{
			if (!LoadFromFile(file_path))
			{
				Logger::Write("Cant load mesh file: " + file_path);
				throw std::invalid_argument("Invalid file path");
			}

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

		void Render()
		{
			unsigned int stride = sizeof(T);
			unsigned int offset = 0;

			device_context_->IASetVertexBuffers(0, 1, &vertex_buffer_, &stride, &offset);
			device_context_->IASetIndexBuffer(index_buffer_, DXGI_FORMAT_R32_UINT, 0);
			device_context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			device_context_->DrawIndexed(data_.i_count_, 0, 0);
		}

	private:
		bool LoadFromFile(const std::string& file_path)
		{
			std::ifstream fin;
			fin.open(file_path);

			if (fin.fail())
				return false;

			char input;
			unsigned long v_count;

			fin.get(input);
			while (input != ':')
				fin.get(input);

			fin >> v_count;

			unsigned long i_count = v_count;

			std::vector<VertexPTN> vertices;
			vertices.resize(v_count);
			std::vector<unsigned long> indices;
			indices.resize(i_count);

			fin.get(input);
			while (input != ':')
				fin.get(input);
			fin.get(input);
			fin.get(input);

			for (unsigned int i = 0; i < v_count; i++)
			{
				fin >>
					vertices[i].position.x >>
					vertices[i].position.y >>
					vertices[i].position.z;
				fin >>
					vertices[i].texture.x >>
					vertices[i].texture.y;
				fin >>
					vertices[i].normal.x >>
					vertices[i].normal.y >>
					vertices[i].normal.z;
			}


			fin.close();

			for (unsigned long i = 0; i < v_count; i++)
				indices[i] = i;

			data_ = MeshData<VertexPTN>(vertices, indices);

			return true;
		}

		bool CreateVertexBuffer()
		{
			D3D11_BUFFER_DESC vertex_buffer_desc;
			vertex_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
			vertex_buffer_desc.ByteWidth = sizeof(T) * data_.v_count_;
			vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			vertex_buffer_desc.CPUAccessFlags = 0;
			vertex_buffer_desc.MiscFlags = 0;
			vertex_buffer_desc.StructureByteStride = 0;

			D3D11_SUBRESOURCE_DATA vertex_buffer_data;
			vertex_buffer_data.pSysMem = data_.v_.data();
			vertex_buffer_data.SysMemPitch = 0;
			vertex_buffer_data.SysMemSlicePitch = 0;

			HRESULT hr = device_->CreateBuffer(&vertex_buffer_desc, &vertex_buffer_data, &vertex_buffer_);
			if (FAILED(hr))
			{
				return false;
			}

			return true;
		}

		bool CreateIndexBuffer()
		{
			D3D11_BUFFER_DESC index_buffer_desc;
			index_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
			index_buffer_desc.ByteWidth = sizeof(unsigned long) * data_.i_count_;
			index_buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			index_buffer_desc.CPUAccessFlags = 0;
			index_buffer_desc.MiscFlags = 0;
			index_buffer_desc.StructureByteStride = 0;

			D3D11_SUBRESOURCE_DATA index_data;
			index_data.pSysMem = data_.i_.data();
			index_data.SysMemPitch = 0;
			index_data.SysMemSlicePitch = 0;

			HRESULT hr = device_->CreateBuffer(&index_buffer_desc, &index_data, &index_buffer_);
			if (FAILED(hr))
			{
				return false;
			}

			return true;
		}

	private:
		std::shared_ptr<ID3D11Device> device_;
		std::shared_ptr<ID3D11DeviceContext> device_context_;

		MeshData<T> data_;

		ID3D11Buffer* vertex_buffer_;
		ID3D11Buffer* index_buffer_;
	};
}

#endif