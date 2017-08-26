#ifndef __TESTGAMEOBJECT_H__
#define __TESTGAMEOBJECT_H__

#pragma once

#include "..\..\engine\world\GameObject.h"

class TestGameObject : public CGameObject
{
public:
	virtual void OnInit();
	virtual void OnUpdate();

private:
	CMesh* m_mesh;
};

#endif