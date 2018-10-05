#ifndef VOODOO_MESH_MANAGER_H_
#define VOODOO_MESH_MANAGER_H_

#include "asset_manager.h"
#include "mesh.h"

namespace voodoo
{
	class MeshManager : public AssetManager<Mesh>
	{
	public:
		// Temporal singleton
		static MeshManager& Get()
		{
			static MeshManager instance;
			return instance;
		}

	private:
		virtual std::shared_ptr<Mesh> Load(std::string filename) override;
	};
}

#endif