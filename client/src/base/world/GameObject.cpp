#include "GameObject.h"

bool GameObject::Init()
{
	m_mesh = new Mesh;
	if (!m_mesh->Init("../../../Client/src/content/meshes/Cube.txt"))
		std::cerr << "Failed to init object" << std::endl;

	m_position = new Vector3;
	m_scale = new Vector3(1, 1, 1);

	return true;
}

void GameObject::Update()
{
	m_mesh->Render();
}