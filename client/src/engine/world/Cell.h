#ifndef __CELL_H__
#define __CELL_H__

#pragma once

#include <vector>

#include "GameObject.h"
#include "..\utils\Memory.h"
#include "..\math\Vector.h"

class CCell
{
public:
	bool Load();
	void Update();
	void Release();

private:
	std::vector<CGameObject*> m_gameObjects;
	IntVector2* position;
};

#endif