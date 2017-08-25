#ifndef __SCENEOBJECT_H__
#define __SCENEOBJECT_H__

#pragma once

#include "..\math\Vector.h"

class CGameObject
{
public:
	bool Init();
	void Update();

private:
	virtual void OnInit() = 0;
	virtual void OnUpdate() = 0;

public:
	Vector3* m_position;
	Vector3* m_scale;
};

#endif