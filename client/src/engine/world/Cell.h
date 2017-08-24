#ifndef __CELL_H__
#define __CELL_H__

#pragma once

#include <vector>

#include "GameObject.h"
#include "..\math\Vector.h"
#include "..\utils\Memory.h"

class CCell
{
public:
	bool Load();
	void Update();
	void Release();

private:
	std::vector<CGameObject*> m_gameObjects;
	CVector2* position;
};

#endif