#ifndef NIXIE_MESH_H_
#define NIXIE_MESH_H_

#pragma once

#include "d3d.h"
#include "../math/vector.h"


namespace Nixie
{
	struct Vertex
	{
		Vector3 position;
		Vector2 texture;
		Vector3 normal;
	};

	class Mesh
	{
	public:
		Mesh();
		~Mesh();

		bool Init(unsigned long vertex_count, unsigned long index_count, Vertex* vertices, unsigned long* indices);

		void Render(unsigned long index_count, D3D11_PRIMITIVE_TOPOLOGY format);

	private:
		bool CreateVertexBuffer(Vertex* vertices, unsigned long vertex_count);
		bool CreateIndexBuffer(unsigned long* indices, unsigned long index_count);

	private:
		std::shared_ptr<ID3D11Device> device_;
		std::shared_ptr<ID3D11DeviceContext> device_context_;

		ID3D11Buffer* vertex_buffer_;
		ID3D11Buffer* index_buffer_;
	};
}

#endif