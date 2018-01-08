#ifndef MESH_DATA_H
#define MESH_DATA_H

#pragma once

#include <fstream>

#include "d3d.h"

namespace Nixie
{
	class MeshData
	{
	public:
		struct Vertex
		{
			DirectX::SimpleMath::Vector3 position;
			DirectX::SimpleMath::Vector2 texture;
			DirectX::SimpleMath::Vector3 normal;
		};

		MeshData();

		bool Init(char* file_path);
		void Release();

		void Render();

	private:
		bool LoadFile(char* file_path);
		bool InitBuffers();

	private:
		ID3D11Buffer * vertex_buffer_;
		ID3D11Buffer* index_buffer_;

		unsigned long vertex_count_;
		unsigned long index_count_;

		Vertex* vertices_;
	};
}

#endif