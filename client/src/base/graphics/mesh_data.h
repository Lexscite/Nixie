#ifndef MESH_DATA_H
#define MESH_DATA_H

#pragma once

#include <fstream>

#include "texture.h"

class MeshData
{
public:
	struct Vertex
	{
		Vector3 position;
		Vector2 texture;
		Vector3 normal;
	};

	MeshData();

	bool Init(char* file_path);
	void Release();

	void Render();

	ID3D11ShaderResourceView* GetTextureView();

private:
	bool LoadFile(char* file_path);
	bool InitBuffers();

	bool LoadTexture(const wchar_t* file_path);

private:
	ID3D11Buffer* vertex_buffer_;
	ID3D11Buffer* index_buffer_;

	unsigned long vertex_count_;
	unsigned long index_count_;

	Vertex* vertices_;
	Texture* texture_;
};

#endif