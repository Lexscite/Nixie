#include "Cell.h"

bool CCell::Load()
{
	for each (CGameObject* gameObject in m_gameObjects)
	{
		if (!gameObject->Init())
			return false;
	}

	return true;
}

void CCell::Update()
{
	for each (CGameObject* gameObject in m_gameObjects)
		gameObject->Update();
}

void CCell::Release()
{
	for each (CGameObject* gameObject in m_gameObjects)
		safe_delete(gameObject);
}