#include "mesh.h"

namespace Nixie
{
	Mesh::Mesh(char* file_path) :
		file_path_(file_path),
		mesh_data_(new MeshData) {}

	void Mesh::OnInit()
	{
		mesh_data_->Init(file_path_);
	}

	void Mesh::OnUpdate()
	{
		if (Input::IsKeyDown(DirectX::Keyboard::Keys::W) && !Input::IsKeyDown(DirectX::Keyboard::Keys::S))
			GetTransform()->position += Vector3(0, 0, 2 * Time::GetDeltaTime());

		if (Input::IsKeyDown(DirectX::Keyboard::Keys::S) && !Input::IsKeyDown(DirectX::Keyboard::Keys::W))
			GetTransform()->position += Vector3(0, 0, -2 * Time::GetDeltaTime());

		if (Input::IsKeyDown(DirectX::Keyboard::Keys::D) && !Input::IsKeyDown(DirectX::Keyboard::Keys::A))
			GetTransform()->rotation *= Quaternion(0, 1 * Time::GetDeltaTime(), 0, 1);

		if (Input::IsKeyDown(DirectX::Keyboard::Keys::A) && !Input::IsKeyDown(DirectX::Keyboard::Keys::D))
			GetTransform()->rotation *= Quaternion(0, -1 * Time::GetDeltaTime(), 0, 1);
		mesh_data_->Render();
	}
}