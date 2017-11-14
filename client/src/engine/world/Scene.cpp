#include "Scene.h"

bool CScene::Init()
{
	m_clearColor = new Color(150, 150, 150);

	m_currentCell = new CCell;
	
	if (!m_currentCell->Load())
		return false;

	return true;
}

void CScene::Release()
{
	safe_release(m_currentCell);
}

void CScene::Update()
{
	m_currentCell->Update();
}

Color* CScene::GetClearColor()
{
	return m_clearColor;
}