#ifndef VOODOO_MESH_LOADER_H_
#define VOODOO_MESH_LOADER_H_

#include "resource_loader.h"
#include "graphics/mesh.h"

namespace voodoo
{
	class MeshLoader : public ResourceLoader<Mesh>
	{
	public:
		// Temporal singleton
		static MeshLoader& Get()
		{
			static MeshLoader instance;
			return instance;
		}

	private:
		virtual std::shared_ptr<Mesh> ProcessFile(std::string file_path) override;
	};
}

#endif