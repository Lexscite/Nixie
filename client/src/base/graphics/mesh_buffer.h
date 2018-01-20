#ifndef MESH_DATA_H
#define MESH_DATA_H

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

	class MeshBuffer
	{
	public:
		MeshBuffer() : vertex_buffer(nullptr), index_buffer(nullptr) {}

		bool Init(unsigned long vertex_count, unsigned long index_count, Vertex* vertices, unsigned long* indices);
		void Release();

		void Render(unsigned long index_count, D3D11_PRIMITIVE_TOPOLOGY format);

	private:
		ID3D11Buffer * vertex_buffer;
		ID3D11Buffer* index_buffer;
	};
}

#endif