#ifndef NIXIE_MESH_LOADER_H_
#define NIXIE_MESH_LOADER_H_

#pragma once

#include "graphics/mesh.h"


namespace nixie
{
	class MeshLoader
	{
	public:
		static MeshLoader& Get();

		std::shared_ptr<Mesh> Load(std::string file_path);
		void Unload(std::string file_path);

	private:
		MeshLoader();

		std::shared_ptr<Mesh> ProcessFile(std::string file_path);

	private:
		std::map<std::string, std::shared_ptr<Mesh>> meshes_;
	};
}

#endif