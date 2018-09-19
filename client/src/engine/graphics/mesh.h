#ifndef NIXIE_MESH_H_
#define NIXIE_MESH_H_

#pragma once

#include "directx_manager.h"
#include "vertex.h"
#include "../logger.h"


namespace nixie
{
	class Mesh
	{
	public:
		Mesh(std::string file_path);
		Mesh(std::vector<VertexPTN> v);

		bool Init();
		void Render();

	private:
		bool LoadFromFile(const std::string& file_path);
		bool LoadObj(const std::string& file_path);
		bool CreateVertexBuffer();
		bool CreateIndexBuffer();

	private:
		std::shared_ptr<ID3D11Device> device_;
		std::shared_ptr<ID3D11DeviceContext> device_context_;

		std::vector<VertexPTN> v_;
		unsigned long v_count_;

		std::vector<unsigned long> i_;
		unsigned long i_count_;

		ID3D11Buffer* vertex_buffer_;
		ID3D11Buffer* index_buffer_;
	};
}

#endif