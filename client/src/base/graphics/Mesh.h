#ifndef MESH_H
#define MESH_H

#pragma once

#include <fstream>

#include "..\utils\Memory.h"
#include  "..\math\Color.h"
#include "D3D.h"

class Mesh
{
private:
	struct VertexType
	{
		Vector3 position;
		Vector3 normal;
		Color color;
	};
	
	struct ModelType
	{
		float x, y, z;
		float nx, ny, nz;
	};

public:
	Mesh();
	bool Init(char* file_path);
	void Release();
	bool LoadFile(char* file_path);
	void Render();
	int GetIndexCount();

private:
	bool InitBuffers();
	void RenderBuffers();

private:
	ID3D11Buffer* vertex_buffer_;
	ID3D11Buffer* index_buffer_;
	int vertex_count_;
	int index_count_;

	ModelType* data_;
};

#endif