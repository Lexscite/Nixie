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
	bool Init(char* filePath);
	void Release();
	bool LoadFile(char* filePath);
	void Render();
	int GetIndexCount();

private:
	bool InitBuffers();
	void RenderBuffers();

	bool ApplyMaterial();

private:
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;
	int m_vertexCount;
	int m_indexCount;

	ModelType* m_meshData;
};

#endif