#include "GameObject.h"

bool CGameObject::Init()
{
	m_position = Vector3::Zero();
	m_scale = new Vector3(1, 1, 1);

	OnInit();

	return true;
}

void CGameObject::Update()
{
	OnUpdate();
}