#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H_

#pragma once

#include "../math/Vector.h"
#include "../graphics/Mesh.h"
#include "../graphics/ColorShader.h"

class GameObject
{
public:
	bool Init();
	void Update();

	Mesh* GetMesh();
	ColorShader* GetShader();

public:
	Vector3* position_;
	Vector3* scale_;

private:
	Mesh* mesh_;
	ColorShader* shader_;
};

#endif