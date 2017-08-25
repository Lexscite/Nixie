#ifndef __SCENE_H__
#define __SCENE_H__

#pragma once

#include <vector>

#include "GameObject.h"
#include "..\utils\Memory.h"
#include "..\math\Vector.h"

struct Cell
{
	std::vector<CGameObject*> m_gameObjects;
	Vector2* position;
};

class CScene
{
public:
	bool Init();
	void Release();
	void Update();

private:
	Cell* m_currentCell;
};

#endif