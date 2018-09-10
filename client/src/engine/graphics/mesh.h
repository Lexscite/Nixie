#ifndef NIXIE_MESH_H_
#define NIXIE_MESH_H_

#pragma once

#include "d3d.h"
#include "../math/vector2.h"
#include "../math/vector3.h"


namespace Nixie
{
	struct Vertex
	{
		Vector3<float> position;
		Vector2<float> texture;
		Vector3<float> normal;
	};

	class Mesh
	{
	public:
		Mesh();
		~Mesh();

		bool Init(std::string file_path);

		void Render();

	private:
		bool LoadFromFile(std::string file_path);

		bool CreateVertexBuffer();
		bool CreateIndexBuffer();

	private:
		std::shared_ptr<ID3D11Device> device_;
		std::shared_ptr<ID3D11DeviceContext> device_context_;

		unsigned long vertex_count_;
		unsigned long index_count_;

		Vertex* vertices_;
		unsigned long* indices_;

		ID3D11Buffer* vertex_buffer_;
		ID3D11Buffer* index_buffer_;
	};
}

#endif