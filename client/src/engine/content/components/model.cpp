#include "../../../stdafx.h"

#include "model.h"


namespace Nixie
{
	Mesh::Mesh(char* file_path) :
		file_path(file_path),
		buffer(new MeshBuffer) {}


	void Mesh::OnInit()
	{
		if (LoadFile(file_path))
		{
			buffer->Init(vertex_count, index_count, vertices, indices);
		}
	}


	void Mesh::OnUpdate()
	{
		buffer->Render(index_count, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}


	bool Mesh::LoadFile(char* file_path)
	{
		std::ifstream fin;
		fin.open(file_path);

		if (fin.fail())
			return false;

		char input;
		fin.get(input);
		while (input != ':')
			fin.get(input);

		fin >> vertex_count;

		index_count = vertex_count;
		vertices = new Vertex[vertex_count];

		fin.get(input);
		while (input != ':')
			fin.get(input);
		fin.get(input);
		fin.get(input);

		for (unsigned int i = 0; i < vertex_count; i++)
		{
			fin >>
				vertices[i].position.x >>
				vertices[i].position.y >>
				vertices[i].position.z;
			fin >>
				vertices[i].texture.x >>
				vertices[i].texture.y;
			fin >>
				vertices[i].normal.x >>
				vertices[i].normal.y >>
				vertices[i].normal.z;
		}

		fin.close();

		indices = new unsigned long[index_count];
		for (unsigned int i = 0; i < vertex_count; i++)
			indices[i] = i;

		return true;
	}
}