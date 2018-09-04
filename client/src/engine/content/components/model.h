#ifndef NIXIE_MODEL_H_
#define NIXIE_MODEL_H_

#pragma once

#include "../component.h"
#include "../../graphics/mesh_buffer.h"


namespace Nixie
{
	class Mesh : public Component
	{
	public:
		Mesh(std::string file_path);

	private:
		virtual void OnInit() override;
		virtual void OnUpdate() override;

		bool LoadFile(std::string file_path);

	private:
		std::string file_path;

		unsigned long vertex_count;
		unsigned long index_count;

		Vertex* vertices;
		unsigned long* indices;

		MeshBuffer* buffer;
	};
}

#endif