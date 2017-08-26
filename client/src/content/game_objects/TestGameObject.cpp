#include "TestGameObject.h"

void TestGameObject::OnInit()
{
	m_mesh = new CMesh;
	if (!m_mesh->Init("../../../Client/src/content/meshes/Cube.txt"))
		std::cerr << "Failed to init object" << std::endl;
}

void TestGameObject::OnUpdate()
{
	m_mesh->Render();
}