#ifndef __MESH_H__
#define __MESH_H__

#pragma once

#include <fstream>
#include "..\utils\Memory.h"
#include  "..\math\Color.h"
#include "DirectX.h"

class CMesh
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
	CMesh();
	bool Init(char* filePath);
	void Release();
	bool Load(char* filePath);
	void Render();
	int GetIndexCount();

private:
	bool InitBuffers();
	void RenderBuffers();

private:
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;
	int m_vertexCount;
	int m_indexCount;

	ModelType* m_meshData;
};

#endif