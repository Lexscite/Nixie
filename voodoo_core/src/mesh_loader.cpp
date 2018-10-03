#include "voodoo/mesh_loader.h"

#include <fstream>

namespace voodoo
{
	std::shared_ptr<Mesh> MeshLoader::ProcessFile(std::string file_path)
	{
		std::ifstream fin;
		fin.open(file_path);

		if (fin.fail())
			throw std::runtime_error("Failed to process mesh file: \"" + file_path + "\"");

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

		std::vector<VertexPTN> v;
		v.resize(v_count);

		for (unsigned int i = 0; i < v_count; i++) {
			fin >>
				v[i].position.x >>
				v[i].position.y >>
				v[i].position.z;
			fin >>
				v[i].texture.x >>
				v[i].texture.y;
			fin >>
				v[i].normal.x >>
				v[i].normal.y >>
				v[i].normal.z;
		}

		fin.close();

		return std::make_shared<Mesh>(v);
	}
}