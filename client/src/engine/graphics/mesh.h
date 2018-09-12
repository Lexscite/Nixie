#ifndef NIXIE_MESH_H_
#define NIXIE_MESH_H_

#pragma once

#include "d3d.h"
#include "../math/vector.h"


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

		bool Init(const std::string& file_path);
		bool Init(const std::vector<Vertex>& vertices);

		void Render();

	private:
		bool LoadFromFile(const std::string& file_path);

		bool CreateVertexBuffer();
		bool CreateIndexBuffer();

	private:
		std::shared_ptr<ID3D11Device> device_;
		std::shared_ptr<ID3D11DeviceContext> device_context_;

		unsigned long vertex_count_;
		unsigned long index_count_;

		std::vector<Vertex> vertices_;
		std::vector<unsigned long> indices_;

		ID3D11Buffer* vertex_buffer_;
		ID3D11Buffer* index_buffer_;
	};
}

#endif