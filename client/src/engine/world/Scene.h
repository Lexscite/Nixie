#ifndef __SCENE_H__
#define __SCENE_H__

#pragma once

#include "..\math\Color.h"
#include "Cell.h"

class CScene
{
public:
	bool Init();
	void Release();
	void Update();

	Color* GetClearColor();

private:
	CCell* m_currentCell;

	Color* m_clearColor;
};

#endif