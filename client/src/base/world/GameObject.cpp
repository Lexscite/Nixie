#include "GameObject.h"

bool GameObject::Init()
{
	position_ = new Vector3(0, 0, 0);
	scale_ = new Vector3(1, 1, 1);

	mesh_ = new Mesh;
	if (!mesh_->Init("../data/meshes/Cube.txt", position_))
		return false;

	shader_ = new ColorShader;
	if (!shader_)
		return false;

	if (!shader_->Init())
		return false;

	return true;
}

void GameObject::Update()
{
}

Mesh* GameObject::GetMesh()
{
	return mesh_;
}

ColorShader* GameObject::GetShader()
{
	return shader_;
}