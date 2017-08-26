#include "Cell.h"
#include "..\..\content\game_objects\TestGameObject.h"

bool CCell::Load()
{
	// test game object
	TestGameObject* tgo = new TestGameObject;

	m_gameObjects.push_back(tgo);

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