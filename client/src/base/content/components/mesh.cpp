#include "mesh.h"

namespace Nixie
{
	Mesh::Mesh(char* file_path)
	{
		file_path_ = file_path;
		mesh_data_ = new MeshData();
	}

	void Mesh::OnInit()
	{
		mesh_data_->Init(file_path_);
	}

	void Mesh::OnUpdate()
	{
		Rotate(Quaternion(0.0f, 1.0f * Time::GetDeltaTime(), 0.0f, 0.5f * Time::GetDeltaTime()));
		mesh_data_->Render();
	}
}