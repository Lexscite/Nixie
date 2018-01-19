#include "mesh.h"

namespace Nixie
{
	Mesh::Mesh(char* file_path) :
		file_path(file_path),
		buffer(new MeshBuffer) {}

	void Mesh::OnInit()
	{
		if (LoadFile(file_path))
		{
			buffer->Init(index_count, vertex_count, vertices);
		}
	}

	void Mesh::OnUpdate()
	{
		if (Input::IsKeyDown(DirectX::Keyboard::Keys::W) && !Input::IsKeyDown(DirectX::Keyboard::Keys::S))
			GetTransform()->Translate(GetTransform()->GetForward() * Time::GetDeltaTime());

		if (Input::IsKeyDown(DirectX::Keyboard::Keys::S) && !Input::IsKeyDown(DirectX::Keyboard::Keys::W))
			GetTransform()->Translate(GetTransform()->GetBackward() * Time::GetDeltaTime());

		if (Input::IsKeyDown(DirectX::Keyboard::Keys::D) && !Input::IsKeyDown(DirectX::Keyboard::Keys::A))
			GetTransform()->Rotate(Quaternion(0, 1 * Time::GetDeltaTime(), 0, 1));

		if (Input::IsKeyDown(DirectX::Keyboard::Keys::A) && !Input::IsKeyDown(DirectX::Keyboard::Keys::D))
			GetTransform()->Rotate(Quaternion(0, -1 * Time::GetDeltaTime(), 0, 1));

		buffer->Render(index_count);
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

		return true;
	}
}