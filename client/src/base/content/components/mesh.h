#ifndef MESH_H
#define MESH_H

#pragma once

#include <fstream>

#include "../../utils/memory.h"
#include "../../math/color.h"
#include "../../graphics/d3d.h"
#include "../component.h"

class Mesh : public Component
{
private:
	struct Vertex
	{
		Vector3 position;
		Vector2 texture;
		Vector3 normal;
	};

public:
	Mesh(char* file_path);

	void Release();
	bool LoadFile();
	int GetIndexCount();

private:
	virtual void OnInit() override;
	virtual void OnUpdate() override;

	bool InitBuffers();
	void RenderBuffers();
	void UpdateVertices();

private:
	char* file_path_;

	ID3D11Buffer* vertex_buffer_;
	ID3D11Buffer* index_buffer_;
	int vertex_count_;
	int index_count_;

	Vertex* vertices_;
};

#endif