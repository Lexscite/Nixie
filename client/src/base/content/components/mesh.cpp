#include "mesh.h"

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
	mesh_data_->Render();
}