#ifndef VOODOO_MESH_H_
#define VOODOO_MESH_H_

#pragma once

#include "directx_manager.h"
#include "vertex.h"


namespace voodoo
{
	class Mesh
	{
	public:
		Mesh();
		Mesh(std::vector<VertexPTN> v);

		bool CreateBuffers();

		unsigned long GetVertexCount();
		unsigned long GetIndexCount();

		std::vector<VertexPTN> GetVertices();
		std::vector<unsigned long> GetIndices();

		ID3D11Buffer* GetVertexBuffer();
		ID3D11Buffer* GetIndexBuffer();

	protected:
		bool CreateVertexBuffer();
		bool CreateIndexBuffer();

	protected:
		std::shared_ptr<ID3D11Device> device_;
		std::shared_ptr<ID3D11DeviceContext> device_context_;

		unsigned long v_count_;
		unsigned long i_count_;

		std::vector<VertexPTN> v_;
		std::vector<unsigned long> i_;

		ID3D11Buffer* vertex_buffer_;
		ID3D11Buffer* index_buffer_;
	};
}

#endif