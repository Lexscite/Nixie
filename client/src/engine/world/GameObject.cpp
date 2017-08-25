#include "GameObject.h"

bool CGameObject::Init()
{
	m_position = Vector3::Zero();
	m_scale = new Vector3(1, 1, 1);
	m_isStatic = false;

	OnInit();

	return true;
}

void CGameObject::Update()
{
	if (m_isStatic)
		return;

	OnUpdate();
}