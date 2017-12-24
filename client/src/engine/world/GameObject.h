#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H_

#pragma once

#include "..\math\Vector.h"
#include "..\graphics\Mesh.h"

class GameObject
{
public:
	bool Init();
	void Update();

public:
	Vector3* m_position;
	Vector3* m_scale;

private:
	Mesh * m_mesh;
};

#endif