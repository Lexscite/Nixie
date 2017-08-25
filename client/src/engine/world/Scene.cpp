#include "Scene.h"

bool CScene::Init()
{
	m_currentCell = new Cell;

	for (int i = 0; i < (int)m_currentCell->m_gameObjects.size(); i++)
	{
		if (!(int)m_currentCell->m_gameObjects[i]->Init())
			return false;
	}

	return true;
}

void CScene::Release()
{
	for (int i = 0; i < (int)m_currentCell->m_gameObjects.size(); i++)
	{
		safe_delete(m_currentCell->m_gameObjects[i]);
	}

	safe_delete(m_currentCell);
}

void CScene::Update()
{
	for (int i = 0; i < (int)m_currentCell->m_gameObjects.size(); i++)
	{
		m_currentCell->m_gameObjects[i]->Update();
	}
}