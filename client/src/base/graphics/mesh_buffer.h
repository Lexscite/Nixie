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

		bool Init(unsigned long index_count, unsigned long vertex_count, Vertex* vertices);
		void Release();

		void Render(unsigned long index_count);

	private:
		ID3D11Buffer * vertex_buffer;
		ID3D11Buffer* index_buffer;
	};
}

#endif