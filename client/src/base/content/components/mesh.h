#ifndef MESH_H
#define MESH_H

#pragma once

#include "../component.h"
#include "../../graphics/mesh_buffer.h"
#include <fstream>

namespace Nixie
{
	class Mesh : public Component
	{
	public:
		Mesh(char* file_path);

	private:
		virtual void OnInit() override;
		virtual void OnUpdate() override;

		bool LoadFile(char* file_path);

	private:
		char* file_path;

		unsigned long vertex_count;
		unsigned long index_count;

		Vertex* vertices;
		MeshBuffer* buffer;
	};
}

#endif