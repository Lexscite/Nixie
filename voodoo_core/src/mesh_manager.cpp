#include "voodoo/mesh_manager.h"

#include <fstream>

namespace voodoo
{
	std::shared_ptr<Mesh> MeshManager::Load(std::string filename)
	{
		std::ifstream fin;
		fin.open(filename);

		if (fin.fail())
			throw std::runtime_error("Failed to process mesh file: \"" + filename + "\"");

		char input;

		unsigned long v_count;

		fin.get(input);
		while (input != ':')
			fin.get(input);

		fin >> v_count;

		fin.get(input);
		while (input != ':')
			fin.get(input);
		fin.get(input);
		fin.get(input);

		std::vector<VertexPTN> vertices;
		vertices.resize(v_count);

		for (unsigned int i = 0; i < v_count; i++) {
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

		return std::make_shared<Mesh>(vertices);
	}
}