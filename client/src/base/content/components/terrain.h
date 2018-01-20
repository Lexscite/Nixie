#ifndef TERRAIN_H
#define TERRAIN_H

#pragma once

#include "../component.h"
#include "../../graphics/mesh_buffer.h"

namespace Nixie
{
	class Terrain : public Component
	{
	public:
		Terrain();

	private:
		virtual void OnInit() override;
		virtual void OnUpdate() override;

	private:
		int width, height;

		unsigned long vertex_count;
		unsigned long index_count;

		Vertex* vertices;
		unsigned long* indices;

		MeshBuffer* buffer;
	};
}

#endif