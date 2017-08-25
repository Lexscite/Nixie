#ifndef __SCENE_H__
#define __SCENE_H__

#pragma once

#include "Cell.h"

class CScene
{
public:
	bool Init();
	void Release();
	void Update();

private:
	CCell* m_currentCell;
};

#endif