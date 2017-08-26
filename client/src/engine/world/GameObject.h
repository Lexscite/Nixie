#ifndef __SCENEOBJECT_H__
#define __SCENEOBJECT_H__

#pragma once

#include "..\math\Vector.h"
#include "..\graphics\Mesh.h"

class CGameObject
{
public:
	bool Init();
	void Update();

private:
	virtual void OnInit() = 0;
	virtual void OnUpdate() = 0;

public:
	bool m_isStatic;

	Vector3* m_position;
	Vector3* m_scale;
};

#endif