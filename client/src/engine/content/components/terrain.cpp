#include "../../../stdafx.h"

#include "terrain.h"

namespace Nixie
{
	Terrain::Terrain() :
		width(100),
		height(100),
		buffer(new MeshBuffer) {}

	void Terrain::OnInit()
	{
		vertex_count = (width - 1) * (height - 1) * 8;
		index_count = vertex_count;

		vertices = new Vertex[vertex_count];
		indices = new unsigned long[index_count];

		int index = 0;
		float positionX, positionZ;

		for (int j = 0; j < (height - 1); j++)
		{
			for (int i = 0; i < (width - 1); i++)
			{
				// LINE 1
				// Upper left.
				positionX = (float)i;
				positionZ = (float)(j + 1);

				vertices[index].position = Vector3(positionX, 0.0f, positionZ);
				vertices[index].texture = Vector2();
				vertices[index].normal = Vector3();
				indices[index] = index;
				index++;

				// Upper right.
				positionX = (float)(i + 1);
				positionZ = (float)(j + 1);

				vertices[index].position = Vector3(positionX, 0.0f, positionZ);
				vertices[index].texture = Vector2();
				vertices[index].normal = Vector3();
				indices[index] = index;
				index++;

				// LINE 2
				// Upper right.
				positionX = (float)(i + 1);
				positionZ = (float)(j + 1);

				vertices[index].position = Vector3(positionX, 0.0f, positionZ);
				vertices[index].texture = Vector2();
				vertices[index].normal = Vector3();
				indices[index] = index;
				index++;

				// Bottom right.
				positionX = (float)(i + 1);
				positionZ = (float)j;

				vertices[index].position = Vector3(positionX, 0.0f, positionZ);
				vertices[index].texture = Vector2();
				vertices[index].normal = Vector3();
				indices[index] = index;
				index++;

				// LINE 3
				// Bottom right.
				positionX = (float)(i + 1);
				positionZ = (float)j;

				vertices[index].position = Vector3(positionX, 0.0f, positionZ);
				vertices[index].texture = Vector2();
				vertices[index].normal = Vector3();
				indices[index] = index;
				index++;

				// Bottom left.
				positionX = (float)i;
				positionZ = (float)j;

				vertices[index].position = Vector3(positionX, 0.0f, positionZ);
				vertices[index].texture = Vector2();
				vertices[index].normal = Vector3();
				indices[index] = index;
				index++;

				// LINE 4
				// Bottom left.
				positionX = (float)i;
				positionZ = (float)j;

				vertices[index].position = Vector3(positionX, 0.0f, positionZ);
				vertices[index].texture = Vector2();
				vertices[index].normal = Vector3();
				indices[index] = index;
				index++;

				// Upper left.
				positionX = (float)i;
				positionZ = (float)(j + 1);

				vertices[index].position = Vector3(positionX, 0.0f, positionZ);
				vertices[index].texture = Vector2();
				vertices[index].normal = Vector3();
				indices[index] = index;
				index++;
			}
		}

		buffer->Init(vertex_count, index_count, vertices, indices);
	}

	void Terrain::OnUpdate()
	{
		buffer->Render(index_count, D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	}
}