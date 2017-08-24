#include "Cell.h"

bool CCell::Load()
{
	for (int i = 0; i < (int)m_gameObjects.size(); i++)
	{
		if (!m_gameObjects[i]->Init())
			return false;
	}

	return true;
}

void CCell::Update()
{
	for (int i = 0; i < (int)m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->Init();
	}
}

void CCell::Release()
{
	for (int i = 0; i < (int)m_gameObjects.size(); i++)
	{
		safe_release(m_gameObjects[i]);
	}
}